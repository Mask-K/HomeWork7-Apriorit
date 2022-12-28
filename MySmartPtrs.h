#pragma once


template<class T>
class SharedPointer;
template<class T>
class WeakPointer;


template<class T>
class SharedPointer{
private:
    T* ptr;
    unsigned* counter;
    void deleteSharedPtr(){
        if(counter && !--*counter){
            delete ptr;
            delete counter;
        }
        ptr = nullptr;
        counter = nullptr;
    }
public:
    friend WeakPointer<T>;
    SharedPointer(): ptr(new T), counter(new unsigned(0)){};

    SharedPointer(T* otherPtr) : ptr(otherPtr), counter(new unsigned(0)){
        if(ptr)
            ++*counter;
    }
    SharedPointer(const SharedPointer<T>& other) : ptr(other.ptr), counter(other.counter){
        if(ptr)
            ++*counter;
    }
    SharedPointer(const WeakPointer<T>& weakOther) : ptr(weakOther.ptr), counter(weakOther.counter){
        if(ptr)
            ++*counter;
    }
    SharedPointer& operator=(const SharedPointer<T>& other){
         deleteSharedPtr();//if ptr had value we need to remove connection

        ptr = other.ptr;
        counter = other.counter;
        if(ptr)
            ++*counter;
        return *this;
    }

    SharedPointer(SharedPointer<T>&& other)  noexcept : ptr(other.ptr), counter(other.counter){
        other.ptr = nullptr;
        other.counter = nullptr;
    }
    SharedPointer& operator=(SharedPointer<T>&& other) noexcept {
        deleteSharedPtr();//if ptr had value we need to remove connection
        ptr = other.ptr;
        counter = other.counter;
        other.counter = nullptr;
        other.ptr = nullptr;
        return *this;
    }

    T* get() const{
        return ptr;
    }

    void reset(T* otherPtr = nullptr){
        deleteSharedPtr();
        counter = new unsigned(0);
        ptr = otherPtr;
        if(ptr)
            ++*counter;
    }
    explicit operator bool() const{
        return ptr != nullptr;
    }

    unsigned use_count() const{
        if(!counter)
            return 0;
        return *counter;
    }

    T& operator*()const{
        return *ptr;
    }
    T& operator->()const{
        return ptr;
    }
    ~SharedPointer(){
        deleteSharedPtr();
    }
};


template<class T>
class WeakPointer{
private:
    T* ptr;
    unsigned* counter;

public:
    friend SharedPointer<T>;
    WeakPointer(const SharedPointer<T>& sharedOther) : ptr(sharedOther.ptr), counter(sharedOther.counter){}
    WeakPointer(const WeakPointer<T>& other) : ptr(other.ptr), counter(other.counter){}
    WeakPointer() : ptr(nullptr), counter(nullptr){}
    WeakPointer(WeakPointer<T>&& other) : ptr(other.ptr), counter(other.counter){
        other.reset();
    }
    ~WeakPointer(){
        reset();
    }
    WeakPointer& operator=(const SharedPointer<T>& other){
        ptr = other.ptr;
        counter = other.counter;
    }
    WeakPointer& operator=(const WeakPointer<T>& other){
        ptr = other.ptr;
        counter = other.counter;
    }
    WeakPointer& operator=(WeakPointer<T>&& other){
        ptr = other.ptr;
        counter = other.counter;
        other.reset();
    }
    void reset(){
        ptr = nullptr;
        counter = nullptr;
    }
    unsigned use_count(){
        if(!counter)
            return 0;
        return *counter;
    }
    bool expired(){
        if(!counter)
            return true;
        return *counter == 0;
    }
    SharedPointer<T> lock(){
        if(expired())
            return nullptr;
        SharedPointer<T> temp;
        temp.ptr = ptr;
        temp.counter = counter;
        ++*counter;
        return std::move(temp);
    }


};

