#include <iostream>
#include <vector>


class obj{
    private:
    std::vector<int>* ptr;

    public:
    //costructor
    obj(){
        ptr = new std::vector<int>;
        std::cout<<"Costructor"<<std::endl;
    }

    //copy costructor
    obj(const obj& other){
        std::cout<<"Copy costructor"<<std::endl;
        ptr = new std::vector<int>;
        *ptr= *other.ptr;
    }
    
    //copy assignment operator
    obj& operator = (const obj& other){
        std::cout<<"copy assignment operator"<<std::endl;
        delete ptr;
        ptr = new std::vector<int>;
        *ptr= *other.ptr;
        return *this;
    }

    //move costructor
    obj(obj&& other) noexcept{
        std::cout<<"move costructor"<<std::endl;
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    //move assignment operator
    obj& operator= (obj&& other) noexcept{
        std::cout<<"move assignment operator"<<std::endl;
        delete ptr;
        ptr= new std::vector<int>;
        *ptr = *other.ptr;
        other.ptr = nullptr;
        return *this;
    }

    //destructor
    ~obj(){
        std::cout<<"destructor"<<std::endl;
        delete ptr;
    }
};


int main() {
    obj a;
    obj b = a;         // Copy constructor
    obj c;             
    c = a;             // Copy assignment
    obj d = std::move(a); // Move constructor
    obj e;
    e = std::move(b);     // Move assignment
}