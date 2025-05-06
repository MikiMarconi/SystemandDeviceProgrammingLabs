#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

std::queue<int> buffer;
std::condition_variable cv;
std::mutex mtx;

void produce(){


    for(int i=0; i<3; ++i){
        mtx.lock();
        int val= rand();
        buffer.emplace(val);
        std::cout<<"Valore inserito: "<< val << std::endl;
        mtx.unlock();
        cv.notify_all();
    }

}

void consume(){

    std::unique_lock<std::mutex> lock(mtx); 
    while (buffer.empty() || buffer.size()<2)
    {
        cv.wait(lock);
    }

    for(int i=0; i<2; ++i){
        std::cout<<"Consumato: "<<buffer.front()<<std::endl;
        buffer.pop();
    }
}

int main(){
    std::srand(std::time(nullptr)); // inizializza il seed con l'orario corrente

    int NP, NC;
    std::cout<<"Inserisci il numero di producer: ";
    std::cin>>NP;
    std::cout<<"Inserisci il numero di consumer: ";
    std::cin>>NC;

    std::vector<std::thread> producer;
    std::vector<std::thread> consumer;
 
    for(int i=0;i<NP;++i){
        producer.emplace_back(std::thread(produce));
    }

    for(int i=0;i<NC;++i){
        consumer.emplace_back(std::thread(consume));
    }

    for (auto& t : producer)
    {
        t.join();
    }

    for (auto& t : consumer)
    {
        t.join();
    }
    

    while(!buffer.empty())
    {
        std::cout<<buffer.front()<<std::endl;
        buffer.pop();
    }
    

}



