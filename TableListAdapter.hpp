
#pragma once

#include "Util.hpp"

#ifdef __APPLE__

#include <UIKit/UIKit.h>

#else

#include <jni.h>

#endif

#include <map>
#include <memory>
#include <iostream>
#include <functional>
#include <stdexcept>
#include "Disposable.hpp"

namespace Mitsoko {
//    using std::cout;
//    using std::endl;
    
    struct DataSourceBase {
        std::function<int()> getSectionsCountLambda;
        
        virtual int getSectionsCount();
        
        std::function<int(int)> getRowsCountLambda;
        
        virtual int getRowsCount(int section);
        
        std::function<std::string(int,int)> getItemIdLambda;
        
        virtual std::string getItemId(int section,int row);
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
    struct DataSource : public DataSourceBase {
        typedef T data_type;
        typedef DataSource<T> Super;
        
        std::function<data_type(int,int)> getItemLambda;
        
        virtual data_type getItem(int section,int row) throw (std::runtime_error){
            if(this->getItemLambda){
                return std::move(this->getItemLambda(section,row));
            }else{
                throw std::runtime_error("getItem not impemented. You have either override getItem or assign getItemLambda to dataSource");
            }
        };
    };
    
    /**
     *  This is a base ckass for adapter. All adapters are stored as pointers to
     *  instances of this class.
     *  Disposable is inherited for image caching callbacks.
     */
    struct AdapterBase : public Mitsoko::Disposable{
        
        /**
         *  UITableViewCellStyle mirror enum. Used in iOS only.
         */
        enum class RowStyle{
            Default
#ifdef __APPLE__
            =UITableViewCellStyleDefault
#endif
            ,
            Value1
#ifdef __APPLE__
            =UITableViewCellStyleValue1
#endif
            ,
            Value2
#ifdef __APPLE__
            =UITableViewCellStyleValue2
#endif
            ,
            Subtitle
#ifdef __APPLE__
            =UITableViewCellStyleSubtitle
#endif
            ,
        };
        
        virtual ~AdapterBase();
        
        /**
         *  This function should be bound to presenter cause in Viper
         *  presenters receive event from views.
         */
        std::function<void(int,int)> rowSelectedLambda;
        
#ifdef __ANDROID__
        
        /**
         *  Adapter stores activity handle (or fragment handle) in android. Actually this is a global pointer to activity or fragement
         *  that helps obtaining context dunring calling `findViewById`.
         *  Context is required almost everywhere. This is why it is very important to store a
         *  pointer to it inside adapter. This value must be assigned manually.
         */
        const void *activityHandle = nullptr;
#endif
        
        virtual void onRowSelected(int section,int row);
        
        virtual void onCreateCell(const void *cell,int section,int row)=0;
        
        virtual void onDisplayCell(const void *cell,int section,int row)=0;
        
        virtual void didEndDisplayingCell(const void *cell,int section,int row)=0;
        
        virtual std::string getViewClass(int section,int row)=0;
        
        virtual RowStyle getRowStyle(int section,int row)=0;
        
        virtual double getRowHeight(int section,int row)=0;
        
        /**
         *  Optional.
         */
        std::function<std::string(int)> getHeaderClassLambda;
        
        virtual std::string getHeaderClass(int section);
        
        /**
         *  Optional.
         */
        std::function<double(int)> getHeaderHeightLambda;
        virtual double getHeaderHeight(int section);
        
        /**
         *  Optional.
         */
        std::function<void(const void*,int)> onCreateHeaderLambda;
        virtual void onCreateHeader(const void *headerHandle,int section);
        
        virtual auto getDataSource()->std::shared_ptr<DataSourceBase> =0;
    };
    
    /**
     *  Adapter is a class which adaptates data from data source to row/cell views.
     *  You can customize adapters in two ways: either create a subclass and override
     *  required functions or create Adater<T> instace without inheritance and assign
     *  appropriate lambdas to it.
     */
    template<class T>
    struct Adapter : public AdapterBase{
        typedef T data_type;
        typedef DataSource<data_type> data_source_type;
        
        /**
         *  Constructor from straight variable is comfortable if dataSource
         *  is not subclassed but implemented with lambdas. If your dataSource is
         *  subclassed - use c-stor `Adapter(std::shared_ptr<data_source_type>)`.
         */
        Adapter(data_source_type ds):Adapter(std::make_shared<data_source_type>(std::move(ds))){}
        
        /**
         *  Constructor with smart pointer used if your dataSource inherits from
         *  DataSource.
         */
        Adapter(std::shared_ptr<data_source_type> dsPointer):dataSource(std::move(dsPointer)){}
        
        std::function<void(const void*,int,int,const data_type&)> onCreateCellLambda;
        std::function<void(const void*,int,int,const data_type&)> onDisplayCellLambda;
        std::function<void(const void*,int,int,const data_type&)> didEndDisplayingCellLambda;
        std::function<std::string(int,int,const data_type&)> getViewClassLambda;
        std::function<RowStyle(int,int,const data_type&)> getRowStyleLambda;
        std::function<double(int,int,const data_type&)> getRowHeightLambda;
        
        virtual void onCreateCell(const void *cellHandle,int section,int row,const data_type &item) throw (std::runtime_error){
            if(this->onCreateCellLambda){
                this->onCreateCellLambda(cellHandle, section, row, item);
            }else{
                throw std::runtime_error("onCreateCell is not implemented. Either implement it in you adapter subclass or assign onCreateCellLambda to your adapter instance");
            }
        }
        
        virtual void onDisplayCell(const void *cellHandle,int section,int row,const data_type &item){
            if(this->onDisplayCellLambda){
                this->onDisplayCellLambda(cellHandle, section, row, item);
            }
        }
        
        virtual void didEndDisplayingCell(const void *cell, int section, int row, const data_type &item){
            if(this->didEndDisplayingCellLambda){
                this->didEndDisplayingCellLambda(cell, section, row, item);
            }
        }
        
        virtual RowStyle getRowStyle(int section,int row,const data_type &item){
            if(this->getRowStyleLambda){
                return this->getRowStyleLambda(section, row, item);
            }else{
                return AdapterBase::RowStyle::Default;
            }
        }
        
        virtual std::string getViewClass(int section,int row,const data_type &item) throw (std::runtime_error){
            if(this->getViewClassLambda){
                return std::move(this->getViewClassLambda(section,row,item));
            }else{
                throw std::runtime_error("getViewClass is not implemented. Either implement it in you adapter subclass or assign getViewClassLambda to your adapter instance");
            }
        }
        
        virtual double getRowHeight(int section,int row,const data_type &item){
            if(this->getRowHeightLambda){
                return getRowHeightLambda(section,row,item);
            }else{
                return 44;
            }
        }
        
        virtual void didEndDisplayingCell(const void *cell,int section,int row) override final{
            this->didEndDisplayingCell(cell, section, row, this->dataSource->getItem(section,row));
        }
        
        virtual double getRowHeight(int section,int row) override{
            return this->getRowHeight(section,row,this->dataSource->getItem(section,row));
        }
        
        virtual RowStyle getRowStyle(int section,int row) override{
            return this->getRowStyle(section,row,this->dataSource->getItem(section,row));
        }
        
        virtual std::shared_ptr<DataSourceBase> getDataSource() override final{
            return std::dynamic_pointer_cast<DataSourceBase>(this->dataSource);
        }
        
        virtual void onCreateCell(const void *cell,int section,int row) override{
            this->onCreateCell(cell,section,row,this->dataSource->getItem(section,row));
        }
        
        virtual void onDisplayCell(const void *cell,int section,int row) override{
            this->onDisplayCell(cell,section,row,this->dataSource->getItem(section,row));
        }
        
        virtual std::string getViewClass(int section,int row) override{
            return std::move(this->getViewClass(section,row,this->dataSource->getItem(section,row)));
        }

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
        
        static AdapterId registerAdapter(const void *tableOrListView,AdapterBasePointer adapter,const void *jni=nullptr);
        
        static void didEndDisplayingCell(const void *tableOrListView,const void *cell,int section,int row,const void *jni=nullptr);
        
        static void willDisplayCell(const void *tableOrListView,const void *cell,int section,int row,const void *jni=nullptr);
        
        static void didSelectRow(const void *tableOrListView,int section,int row,const void *jni=nullptr);
        
        static double rowHeight(const void *tableOrListView,int section,int row);
        
        static void cellCreated(const void *tableOrListView,const void *cell,int section,int row,const void *jni=nullptr);
        
        /*** iOS only ***/
        static AdapterBase::RowStyle cellStyle(const void *tableOrListView,int section,int row);
        
        static void headerCreated(const void *tableOrListView,const void *header,int section,const void *jni=nullptr);
        
        static double headerHeight(const void *tableOrListView,int section,const void *jni=nullptr);
        
        static std::string headerViewClassName(const void *tableOrListView,int section,const void *jni=nullptr);
        
        static std::string cellClassName(const void *tableOrListView,int section,int row,const void *jni=nullptr);
        
        static std::string rowId(const void *tableOrListView,int section,int row,const void *jni=nullptr);
        
        static int rowsCount(const void *tableOrListView,int section,const void *jni=nullptr);
        
        static int sectionsCount(const void *tableOrListView,const void *jni=nullptr);
        
#ifdef __ANDROID__
        static int getAdapterId(const void *tableOrListView,JNIEnv *java_env);
#endif
        
    protected:
        typedef std::map<AdapterId, AdapterBasePointer> AdaptersMap;
        static AdaptersMap adaptersMap;
//        STATIC_VAR(AdaptersMap, adaptersMap, {});
    };
}
