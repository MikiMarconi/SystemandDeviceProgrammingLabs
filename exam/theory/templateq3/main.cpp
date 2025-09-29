#include <iostream>

template<typename T>
class Box{
    private:
    T value;

    public:
    Box() = default;

    Box(T val){
        value=val;
    }

    T getValue(){
        return value;
    }

    void setValue(T val){
        value=val;
    }

};


int main() {
    Box<int> intBox(123);
    Box<std::string> strBox("Hello");
    Box<float> fB;
    fB.setValue (13.24);
    std::cout << intBox.getValue() << std::endl;
    std::cout << strBox.getValue() << std::endl;
    return 0;
}