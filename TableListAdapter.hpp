
#pragma once

#include "Util.hpp"
#include <map>
#include <memory>
#include <iostream>
#include <functional>
#include <stdexcept>

namespace Viper {
    using std::cout;
    using std::endl;
    
    struct DataSourceBase{
        std::function<int()> getSectionsCountLambda;
        
        virtual auto getSectionsCount()->int{
            if(this->getSectionsCountLambda){
                return getSectionsCountLambda();
            }else{
                return 1;
            }
        }
        
        std::function<int(int)> getRowsCountLambda;
        
        virtual auto getRowsCount(int section)->int{
            if(this->getRowsCountLambda){
                return this->getRowsCountLambda(section);
            }else{
                return 0;
            }
        };
        
        std::function<std::string(int,int)> getItemIdLambda;
        
        virtual auto getItemId(int section,int row)->std::string{
            if(this->getItemIdLambda){
                return std::move(this->getItemIdLambda(section,row));
            }else{
                return {};
            }
        };
    };
    
    /**
     *  Data source is a class managed by presenter. Data source has functions analogs
     *  for *tableView:numberOfRowsInSection:* in **UITableViewDataSource** and *getCount*
     *  in **android.widget.BaseAdapter**.
     *  **T** is a data type transfered into adapter. It cal be anything comfortable: either
     *  pointer to an abstract class inherited by your data type (situation similar to Apple when 
     *  data class implements protocol binds to a row itself as a reference to a protocol instance) or 
     *  a *std::tuple* (or any other POD data type) or even data model itself (this is a non-viper way).
     */
    template<class T>
    struct DataSource:public DataSourceBase{
        typedef T data_type;
        typedef DataSource<T> Super;
        
        std::function<data_type(int,int)> getItemLambda;
        
        virtual auto getItem(int section,int row) throw (std::runtime_error) ->data_type{
            if(this->getItemLambda){
                return std::move(this->getItemLambda(section,row));
            }else{
                throw std::runtime_error("getItem not impemented. You have either override getItem or assign getItemLambda to dataSource");
            }
        };
    };
    
    struct AdapterBase{
        
        /**
         *  This function should be bound to presenter cause in Viper
         *  presenters receive event from views.
         */
        std::function<void(int,int)> rowSelectedLambda;
        
#ifdef __ANDROID__
        const void *activityHandle=nullptr;
#endif
        
        virtual auto onRowSelected(int section,int row)->void {
            if(this->rowSelectedLambda){
                this->rowSelectedLambda(section,row);
            }
        }
        
        std::function<std::string(int,int)> getViewClassLambda;
        
        virtual auto getViewClass(int section,int row) throw (std::runtime_error) ->std::string{
            if(this->getViewClassLambda){
                return std::move(this->getViewClassLambda(section,row));
            }else{
                throw std::runtime_error("getViewClass is not implemented. Either implement it in you adapter subclass or assign getViewClassLambda to your adapter instance");
            }
        }
        
//        std::function<void(const void*,int,int)> onCreateCellLambda;
        
        virtual auto onCreateCell(const void *cell,int section,int row)->void =0;
        /*virtual auto onCreateCell(const void *cell,int section,int row) throw (std::runtime_error) ->void{
            if(this->onCreateCellLambda){
                this->onCreateCellLambda(cell,section,row);
            }else{
                throw std::runtime_error("onCreateCell is not implemented. Either implement it in you adapter subclass or assign onCreateCellLambda to your adapter instance");
            }
        };*/
        
//        std::function<void(const void*,int,int)> onDisplayCellLambda;
        
        virtual auto onDisplayCell(const void *cell,int section,int row)->void =0;
        
        /*virtual auto onDisplayCell(const void *cell,int section,int row)->void{
            if(this->onDisplayCellLambda){
                this->onDisplayCellLambda(cell,section,row);
            }
        };*/
        
        std::function<double(int,int)> getRowHeightLambda;
        
        virtual auto getRowHeight(int section,int row)->double{
            if(this->getRowHeightLambda){
                return this->getRowHeightLambda(section,row);
            }else{
                return 44;
            }
        }
        
        virtual auto getDataSource()->std::shared_ptr<DataSourceBase> =0;
    };
    
    template<class T>
    struct Adapter:public AdapterBase{
        typedef T data_type;
        typedef DataSource<data_type> data_source_type;
        
        Adapter(std::shared_ptr<data_source_type> dsPointer):dataSource(dsPointer){}
        
        virtual auto getDataSource()->std::shared_ptr<DataSourceBase> override{
            return std::dynamic_pointer_cast<DataSourceBase>(this->dataSource);
        }
        
        virtual auto onCreateCell(const void *cell,int section,int row)->void override{
            this->onCreateCell(cell,section,row,this->dataSource->getItem(section,row));
        }
        
        std::function<void(const void*,int,int,const data_type&)> onCreateCellLambda;
        
        virtual auto onCreateCell(const void *cellHandle,int section,int row,const data_type &item) throw (std::runtime_error) ->void{
            if(this->onCreateCellLambda){
                this->onCreateCellLambda(cellHandle,section,row,item);
            }else{
                throw std::runtime_error("onCreateCell is not implemented. Either implement it in you adapter subclass or assign onCreateCellLambda to your adapter instance");
            }
        }
        
        virtual auto onDisplayCell(const void *cell,int section,int row)->void override{
            this->onDisplayCell(cell,section,row,this->dataSource->getItem(section,row));
        }
        
        std::function<void(const void*,int,int,const data_type&)> onDisplayCellLambda;
        
        virtual auto onDisplayCell(const void *cellHandle,int section,int row,const data_type &item)->void{
            if(this->onDisplayCellLambda){
                this->onDisplayCellLambda(cellHandle,section,row,item);
            }
        };
    protected:
        std::shared_ptr<data_source_type> dataSource;
    };
    
    
    /**
     *  This is a service class used for keeping adapter on core side.
     */
    struct TableListAdapter{
        typedef std::shared_ptr<AdapterBase> AdapterBasePointer;
        typedef const void *AdapterId;
        
        constexpr static AdapterId adapterIdNull=nullptr;
        
        static AdapterId registerAdapter(const void *tableOrListView,AdapterBasePointer adapter,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it=adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                if(adapter){
                    it->second=adapter;
                }else{
                    adaptersMap().erase(it);
                }
            }else{
                if(adapter){
#ifdef __APPLE__
                    adaptersMap().insert({tableOrListView,adapter});
#else
                    adaptersMap().insert({(const void*)adapterId,adapter});
#endif
                }else{
                    cout<<"table or list view not found ("<<tableOrListView<<")"<<endl;
                }
            }
#ifdef __APPLE__
            return tableOrListView;
#else
            return AdapterId(adapterId);
#endif
        }
        
        static void willDisplayCell(const void *tableOrListView,const void *cell,int section,int row,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it = adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                it->second->onDisplayCell(cell, section, row);
            }else{
                //  not found..
            }
        }
        
        static void didSelectRow(const void *tableOrListView,int section,int row,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it = adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                it->second->onRowSelected(section, row);
            }else{
                //  not found..
            }
        }
        
        static double rowHeight(const void *tableOrListView,int section,int row){
            auto it=adaptersMap().find(tableOrListView);
            if(it != adaptersMap().end()){
                return it->second->getRowHeight(section, row);
            }else{
                return 0;
            }
        }
        
        static void cellCreated(const void *tableOrListView,const void *cell,int section,int row,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it = adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                it->second->onCreateCell(cell, section, row);
            }else{
                //  not found..
            }
        }
        
        static std::string cellClassName(const void *tableOrListView,int section,int row,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it = adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                return std::move(it->second->getViewClass(section, row));
            }else{
                return 0;
            }
        }
        
        static std::string rowId(const void *tableOrListView,int section,int row,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it = adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                return std::move(it->second->getDataSource()->getItemId(section, row));
            }else{
                return 0;
            }
        }
        
        static int rowsCount(const void *tableOrListView,int section,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it = adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                return it->second->getDataSource()->getRowsCount(section);
            }else{
                return 0;
            }
        }
        
        static int sectionsCount(const void *tableOrListView,const void *jni=nullptr){
            auto it=adaptersMap().end();
#ifdef __APPLE__
            it = adaptersMap().find(tableOrListView);
#else
            auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
            it = adaptersMap().find((const void*)adapterId);
#endif
            if(it != adaptersMap().end()){
                auto adapterBase=it->second;
                auto dataSource=adapterBase->getDataSource();
                auto res=dataSource->getSectionsCount();
                return res;
            }else{
                LOGI("tableOrListView not found in %s",__func__);
                return 0;
            }
        }
        
#ifdef __ANDROID__
        static int getAdapterId(const void *tableOrListView,JNIEnv *java_env){
            if(java_env){
                auto listView=static_cast<jobject>(const_cast<void*>(tableOrListView));
                auto listViewClazz=java_env->GetObjectClass(listView);
                auto getAdapterMethodId=java_env->GetMethodID(listViewClazz,"getAdapter","()Landroid/widget/ListAdapter;");
                auto adapter=java_env->CallObjectMethod(listView,getAdapterMethodId);
                
                auto adapterClazz=java_env->GetObjectClass(adapter);
                auto fieldId=java_env->GetFieldID(adapterClazz,"adapterId","I");
                auto adapterId=java_env->GetIntField(adapter,fieldId);
                return adapterId;
            }else{
                return -1;
            }
        }
#endif
        
    protected:
        typedef std::map<AdapterId, AdapterBasePointer> AdaptersMap;
        STATIC_VAR(AdaptersMap, adaptersMap, {});
    };
}
