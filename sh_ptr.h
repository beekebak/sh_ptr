#include<algorithm>

template <class T>
class shared_ptr{
  public:
    shared_ptr(T* p  = nullptr): ptr_{p}{
        counter = new size_t;
        *counter = 1;
    }
    ~shared_ptr(){
        release_memory();
    }
    shared_ptr(const shared_ptr& other) : ptr_{other.ptr_}, counter{other.counter} {
        (*counter)++;
    }
    shared_ptr(shared_ptr&& other) : ptr_{other.ptr_}, counter{other.counter}{
        (*counter)++;
        other.ptr_ = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& other){
        release_memory();
        ptr_ = other.ptr_;
        counter = other.counter;
        (*counter)++;
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& other){
        (*counter)--;
        ptr_ = other.ptr_;
        counter = other.counter;
        (*counter)++;
        return *this;
    }

    T* get(){
        return ptr_;
    }
    T* reset(T* newnew = nullptr){
        release_memory();
        ptr_ = newnew;
        counter = new size_t;
        *counter = 1;
        return ptr_;
    }
    T* release(){
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }
    T* operator->(){
        return ptr_;
    }
    T& operator*(){
        return *ptr_;
    }

  private:
    void release_memory(){
        (*counter)--;
        if((*counter) == 0) {
            delete ptr_;
            delete counter;
        }
    }
    size_t* counter = nullptr;
    T* ptr_ = nullptr;
};

struct A{};

void pseudo_main(){
    shared_ptr<A> p1;
    shared_ptr<A> p2(new A());
    shared_ptr<A> p3 = p2;
    shared_ptr<A> p4 = p3;
    shared_ptr<A> p5 = p4;

    p2 = p1;
    p1.reset(new A());
    
    p5 = p1;
    shared_ptr<A> p6 = p5;
    shared_ptr<A> p7 = std::move(p6);
    p5 = std::move(p6);
    p5.release();
}