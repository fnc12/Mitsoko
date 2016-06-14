
#pragma once

#include <map>
#include <thread>
#include <mutex>
#include <string>

namespace java{
    namespace lang{
#ifdef __ANDROID__
        /**
         *  This class is a container for JNIEnv pointer needed in android to perform any actions with
         *  JVM objects. It has <i>envMap</i> static <b>std::map<std::thread::id, JNIEnv*></b> with
         *  JNIEnv pointer per thread. This map is protected and is accessed through mutex <b>envMapMutex</b> only.
         *  A JNI instance takes JNIEnv pointer as the only argument and inserts it into <i>envMap</i> if there is no
         *  one already for current thread. Also it erases JNIEnv pointer from <i>envMap</i> in its destructor if 
         *  it is inserted one in constructor.
         *  <i>hasValue</i> is true if JNI instance inserted a new JNIEnv pointer into <i>envMap</i>. It is very important not 
         *  to insert the same pointer for current thread if it is already in the <i>envMap</i> cause if this happens it means
         *  there is two or more JNI instances created. This case is not critical but if latest JNI erase JNIEnv pointer then older
         *  JNI instances will have nothing to erase and android mirror classes will not work cause <b>Env()</b> will return 
         *  <i>nullptr</i> always.
         *  You do not have to create JNI instances on your own. All instances are created in system code in <i>NI.cpp</i> for you.
         *  =========
         *  If you need to access JNIEnv pointer for this thread in your code write `auto env=java::lang::JNI::Env();`.
         */
        struct JNI{
            JNI(JNIEnv *env){
                if(!Env()){
                    insertEnv(env);
                    this->hasValue=true;
                }
            }
            
            ~JNI(){
                if(this->hasValue){
                    removeEnv();
                    this->hasValue=false;
                }
            }
            
            /**
             *  Common public function for accessing current thread JNIEnv pointer.
             */
            static JNIEnv* Env(){
                JNIEnv *res=nullptr;
                
                envMapMutex().lock();
                const auto threadId=std::this_thread::get_id();
                const auto it=envMap().find(threadId);
                if(it!=envMap().end()){
                    res=it->second;
                }
                envMapMutex().unlock();
                
                return res;
            }
            
            /**
             *  This variable is assigned once after NI library is loaded on android.
             *  This variable contains appId like `kz.outlawstudio.groozim`.
             */
            STATIC_VAR(std::string, appId, {});
            
            /**
             *  This variable contains `appId` but with '.' characters replaced with '/'
             *  like `kz/outlawstudio/groozim`. It is created for cache only (for not replacing 
             *  chars every time from appId when appNamespace is needed). `appNamespace` is neede in Viper
             *  classes for accessing helper classes like `ViperTableViewAdapter`.
             */
            STATIC_VAR(std::string, appNamespace, {});
        protected:
            bool hasValue=false;
            
            typedef std::map<std::thread::id, JNIEnv*> JNIEnvMap;
            STATIC_VAR(JNIEnvMap, envMap, {});
            
            void insertEnv(JNIEnv *env){
                const auto threadId=std::this_thread::get_id();
                
                envMapMutex().lock();
                envMap().insert({threadId,env});
                envMapMutex().unlock();
            }
            
            void removeEnv(){
                const auto threadId=std::this_thread::get_id();
                
                envMapMutex().lock();
                const auto it=envMap().find(threadId);
                if(it!=envMap().end()){
                    envMap().erase(it);
                }
                envMapMutex().unlock();
            }
            
            static std::mutex& envMapMutex(){
                static std::mutex res;
                return res;
            }
        };
#endif
    }
}
