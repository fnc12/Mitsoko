//
//  TableListAdapter.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TableListAdapter.hpp"
#include <iostream>

Mitsoko::TableListAdapter::AdaptersMap Mitsoko::TableListAdapter::adaptersMap;

int Mitsoko::DataSourceBase::getSectionsCount(){
    if(this->getSectionsCountLambda){
        return getSectionsCountLambda();
    }else{
        return 1;
    }
}

int Mitsoko::DataSourceBase::getRowsCount(int section){
    if(this->getRowsCountLambda){
        return this->getRowsCountLambda(section);
    }else{
        return 0;
    }
}

std::string Mitsoko::DataSourceBase::getItemId(int section,int row){
    if(this->getItemIdLambda){
        return this->getItemIdLambda(section,row);
    }else{
        return {};
    }
}

Mitsoko::AdapterBase::~AdapterBase(){
    this->dispose();
}

void Mitsoko::AdapterBase::onRowSelected(int section,int row){
    if(this->rowSelectedLambda){
        this->rowSelectedLambda(section,row);
    }
}

std::string Mitsoko::AdapterBase::getHeaderClass(int section){
    if(this->getHeaderClassLambda){
        return this->getHeaderClassLambda(section);
    }else{
        return {};
    }
}

double Mitsoko::AdapterBase::getHeaderHeight(int section){
    if(this->getHeaderHeightLambda){
        return this->getHeaderHeightLambda(section);
    }else{
        return 0;
    }
}

void Mitsoko::AdapterBase::onCreateHeader(const void *headerHandle,int section){
    if(this->onCreateHeaderLambda){
        this->onCreateHeaderLambda(headerHandle,section);
    }
}

Mitsoko::TableListAdapter::AdapterId Mitsoko::TableListAdapter::registerAdapter(const void *tableOrListView,
                                                                                AdapterBasePointer adapter,
                                                                                const void *jni)
{
    auto it=adaptersMap.end();
    it=adaptersMap.find(tableOrListView);
    if(it != adaptersMap.end()){
        if(adapter){
            it->second=adapter;
        }else{
            adaptersMap.erase(it);
        }
    }else{
        if(adapter){
            adaptersMap.insert({tableOrListView,adapter});
        }else{
            std::cerr<<"table or list view not found ("<<tableOrListView<<")"<<std::endl;
        }
    }
    return tableOrListView;
}

void Mitsoko::TableListAdapter::didEndDisplayingCell(const void *tableOrListView, const void *cell, int section, int row, const void *jni){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
    it = adaptersMap.find((const void*)(intptr_t)adapterId);
#endif
    if(it != adaptersMap.end()){
        it->second->didEndDisplayingCell(cell, section, row);
    }else{
        //  not found..
    }
}

void Mitsoko::TableListAdapter::willDisplayCell(const void *tableOrListView,const void *cell,int section,int row,const void *jni){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
    it = adaptersMap.find((const void*)(intptr_t)adapterId);
#endif
    if(it != adaptersMap.end()){
        it->second->onDisplayCell(cell, section, row);
    }else{
        //  not found..
    }
}

void Mitsoko::TableListAdapter::didSelectRow(const void *tableOrListView,int section,int row,const void *jni){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
    it = adaptersMap.find((const void*)(intptr_t)adapterId);
#endif
    if(it != adaptersMap.end()){
        it->second->onRowSelected(section, row);
    }else{
        //  not found..
    }
}

double Mitsoko::TableListAdapter::rowHeight(const void *tableOrListView,int section,int row){
    auto it=adaptersMap.find(tableOrListView);
    if(it != adaptersMap.end()){
        return it->second->getRowHeight(section, row);
    }else{
        return 0;
    }
}

void Mitsoko::TableListAdapter::cellCreated(const void *tableOrListView,const void *cell,int section,int row,const void *jni){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
    it = adaptersMap.find((const void*)(intptr_t)adapterId);
#endif
    if(it != adaptersMap.end()){
        it->second->onCreateCell(cell, section, row);
    }else{
        //  not found..
    }
}

Mitsoko::AdapterBase::RowStyle Mitsoko::TableListAdapter::cellStyle(const void *tableOrListView,int section,int row){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    //..
#endif
    if(it != adaptersMap.end()){
        return it->second->getRowStyle(section,row);
    }else{
        return AdapterBase::RowStyle::Default;
    }
}

void Mitsoko::TableListAdapter::headerCreated(const void *tableOrListView,const void *header,int section,const void *jni){
    auto it=adaptersMap.end();
    it = adaptersMap.find(tableOrListView);
    if(it != adaptersMap.end()){
        it->second->onCreateHeader(header, section);
    }else{
        //  not found..
    }
}

double Mitsoko::TableListAdapter::headerHeight(const void *tableOrListView,int section,const void *jni){
    auto it=adaptersMap.end();
    it = adaptersMap.find(tableOrListView);
    if(it != adaptersMap.end()){
        return it->second->getHeaderHeight(section);
    }else{
        return 0;
    }
}

std::string Mitsoko::TableListAdapter::headerViewClassName(const void *tableOrListView,int section,const void *jni){
    auto it=adaptersMap.end();
    it = adaptersMap.find(tableOrListView);
    if(it != adaptersMap.end()){
        return it->second->getHeaderClass(section);
    }else{
        return "";
    }
}

std::string Mitsoko::TableListAdapter::cellClassName(const void *tableOrListView,int section,int row,const void *jni){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
    it = adaptersMap.find((const void*)(intptr_t)adapterId);
#endif
    if(it != adaptersMap.end()){
        return it->second->getViewClass(section, row);
    }else{
        return 0;
    }
}

std::string Mitsoko::TableListAdapter::rowId(const void *tableOrListView,int section,int row,const void *jni){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
    it = adaptersMap.find((const void*)(intptr_t)adapterId);
#endif
    if(it != adaptersMap.end()){
        return it->second->getDataSource()->getItemId(section, row);
    }else{
        return 0;
    }
}

int Mitsoko::TableListAdapter::rowsCount(const void *tableOrListView,int section,const void *jni){
    auto it=adaptersMap.end();
#ifdef __APPLE__
    it = adaptersMap.find(tableOrListView);
#else
    auto adapterId=getAdapterId(tableOrListView,(JNIEnv*)jni);
    it = adaptersMap.find((const void*)(intptr_t)adapterId);
#endif
    if(it != adaptersMap.end()){
        return it->second->getDataSource()->getRowsCount(section);
    }else{
        return 0;
    }
}

int Mitsoko::TableListAdapter::sectionsCount(const void *tableOrListView,const void *jni){
    auto it=adaptersMap.end();
    it = adaptersMap.find(tableOrListView);
    if(it != adaptersMap.end()){
        auto adapterBase=it->second;
        auto dataSource=adapterBase->getDataSource();
        auto res=dataSource->getSectionsCount();
        return res;
    }else{
        std::cout<<"tableOrListView not found in "<<__func__<<std::endl;
        return 0;
    }
}

#ifdef __ANDROID__
int Mitsoko::TableListAdapter::getAdapterId(const void *tableOrListView,JNIEnv *java_env){
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
