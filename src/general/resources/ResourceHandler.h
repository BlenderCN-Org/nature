#ifndef _RESOURCE_HANDLER_
#define _RESOURCE_HANDLER_
template <class ManagerClass,typename TypeManaged,typename KeyType>
class ResourceHandler{
    TypeManaged* ptr=nullptr;
    KeyType key;
    public:
    ResourceHandler(){
        this->ptr=nullptr;
    };

    ResourceHandler(TypeManaged* ptr,KeyType key){
        this->ptr=ptr;
        this->key=key;
        ManagerClass::instance()->reserve(key);
        std::cout<<"reservando"<<std::endl;
    };

    ResourceHandler(const ResourceHandler& n){
        ptr=n.ptr;
        key=n.key;
        ManagerClass::instance()->reserve(key);
    };
    ResourceHandler& operator=(const ResourceHandler& n){
        ptr=n.ptr;
        key=n.key;
        ManagerClass::instance()->reserve(key);
        return *this;
    };
    ResourceHandler(ResourceHandler&& n){
        std::swap(ptr,n.ptr);
        std::swap(key,n.key);
    };
    ResourceHandler& operator=(ResourceHandler&&n){
        std::swap(ptr,n.ptr);
        std::swap(key,n.key);
        return *this;
    };
    TypeManaged& operator*() const{
        return *ptr;
    }

    virtual ~ResourceHandler(){
        if(ptr!=nullptr){        
            ManagerClass::instance()->release(key);
            std::cout<<"liberando"<<std::endl;
        }
    }

    TypeManaged* operator->(){
        return ptr;
    };
    TypeManaged* get(){
        return ptr;
    }
    bool isValid(){
        return ptr!=nullptr;
    }
};

#endif
