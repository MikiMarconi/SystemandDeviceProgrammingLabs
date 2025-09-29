#include <iostream>
#include <deque>

template<typename T>
class FIFO{
    private:
    std::deque<T> list;

    public:
    void push(T a){
        list.push_back(a);
    }

    void pop(){
        list.pop_front();
    }
};

int main(){

    FIFO<int> f1;
    FIFO<char> f2;
    FIFO<double> f3;
    f1.push(4);
    f2.push('e');
    f3.push(3.4);

}
