#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <random>
#include <chrono>

std::mutex mtx;
std::counting_semaphore<0> semNa(0);
std::counting_semaphore<0> semCl(0);


int randomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (0, 5) (gen);
}

void produceCl(){
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(randomint()));
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"Cl generated"<<std::endl;
        }
        semCl.release();
    }
    
}

void produceNa(){
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(randomint()));
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"Na generated"<<std::endl;
        }
        semNa.release();
    }
}

void produceNaCl(){
    while(true){
        semNa.acquire();
        semCl.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"NaCl generated"<<std::endl;
        }

    }
}

int main(){

    std::thread TCl(produceCl);
    std::thread TNa(produceNa);
    std::thread TNaCl(produceNaCl);

    TCl.join();
    TNa.join();
    TNaCl.join();

    return 0;
}