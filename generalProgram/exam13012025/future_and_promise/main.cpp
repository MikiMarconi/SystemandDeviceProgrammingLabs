#include <iostream>
#include <future>
#include <random>
#include <chrono>
#include <thread>

int randomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (1, 10) (gen);
}

void generateH(std::promise<bool>& p){
    std::this_thread::sleep_for(std::chrono::seconds(randomint()));
    p.set_value(true);
}


void generateH2(std::promise<bool>& p, std::future<bool>& fut){
    if(fut.get()){
        std::this_thread::sleep_for(std::chrono::seconds(randomint()));
        p.set_value(true);
    }
}

void generateO(std::promise<bool>& p, std::future<bool>& fut){
    if(fut.get()){
        std::this_thread::sleep_for(std::chrono::seconds(randomint()));
        p.set_value(true);
    }
}

void generateH2O(std::future<bool>& fut){
    if(fut.get()){
        std::cout<<"H2O generated";
    }
}

int main(){

    std::promise<bool> p1, p2, p3;
    std::future<bool> fut1 = p1.get_future();
    std::future<bool> fut2 = p2.get_future();
    std::future<bool> fut3 = p3.get_future();

    std::thread Hy(generateH, std::ref(p1));
    std::thread H2(generateH2, std::ref(p2), std::ref(fut1));
    std::thread O(generateO, std::ref(p3), std::ref(fut2));
    std::thread H2O(generateH2O, std::ref(fut3));

    H2.join();
    Hy.join();
    O.join();
    H2O.join();

}