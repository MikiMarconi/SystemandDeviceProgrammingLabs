#include <iostream>
#include <thread>
#include <future>

int Fibonacci(int num){
    if(num<2){
        return 1;
    }else{
        auto fut1 = std::async(std::launch::async, Fibonacci, num-1);
        auto fut2 = std::async(std::launch::async, Fibonacci, num-2);
        return fut1.get() + fut2.get();
    }

}

int main(){

    int num;
    std::cout<<"Inserisci valore: ";
    std::cin>>num;
    auto fut = std::async(std::launch::async, Fibonacci, num);

    std::cout<<fut.get();
}