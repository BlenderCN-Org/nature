#ifndef _MANAGER_H_
#define _MANAGER_H_
#include <memory>
#include <map>
#include "ResourceHandler.h"
template <class ManagerClass,typename KeyType,typename TypeManaged>
class Manager{
    private:

        static std::unique_ptr<ManagerClass> _instance;
        std::map<KeyType,std::unique_ptr<TypeManaged>> resources;
        std::map<KeyType,int> counters;
    public:
       
       typedef ResourceHandler<ManagerClass,TypeManaged,KeyType> ResHanType;

/*       static  ManagerClass* instance(Args... args){
           if(_instance==nullptr){
               _instance=std::unique_ptr<ManagerClass>(new ManagerClass(std::forward<Args>))
               _instance=std::unique_ptr<ManagerClass>(new ManagerClass(std::forward<Args>(args)...);
           }
           return _instance.get();
       };*/

       static  ManagerClass* instance(){
           if(_instance==nullptr){
               _instance=std::unique_ptr<ManagerClass>(new ManagerClass());
           }
           return _instance.get();
       };
       ResHanType get(KeyType k){
           if(resources.find(k)!=resources.end()){
               return std::move(ResHanType(resources[k].get(),k));
           }else{
               return std::move(ResHanType(nullptr,k));
           }
       }


       template <typename... Args>
       ResHanType load(KeyType k,Args... args){
           if(!containt(k)){
              set(k,std::unique_ptr<TypeManaged>(new TypeManaged(std::forward<Args>(args)...)));
           }
           return get(k);
       }

       void set(KeyType k,std::unique_ptr<TypeManaged> v){
           if(resources.find(k)==resources.end()){
               resources[k]=std::move(v);
               counters[k]=0;
           }
       }
       bool containt(KeyType k){
           return resources.find(k)!=resources.end();
       }
       void reserve(KeyType key){
            counters[key]++;
       }
       int count(KeyType key){
           return counters[key];
       }
       void release(KeyType key){
            int& c=counters[key];
            c--;

            std::cout<<"contador:"<<c<<";"<<counters[key]<<std::endl;
            if(c<=0){
       //        resources.erase(key); 
            }
       }
};

template <class ManagerClass,typename TypeManaged,typename KeyType>
std::unique_ptr<ManagerClass>  Manager<ManagerClass,TypeManaged,KeyType>::_instance = nullptr;
#endif
