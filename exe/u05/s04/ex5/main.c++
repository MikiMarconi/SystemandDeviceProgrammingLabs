#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <semaphore>
#include <chrono>


int numR=0;
int numW=0;
std::condition_variable cv;
std::mutex mtx;

void read(){

    {    
        std::unique_lock<std::mutex> lock(mtx);
        while (numW!=0)
        {
            cv.wait(lock);
        }

        numR++;
        std::cout<<"Lettore: "<<numR<<std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::unique_lock<std::mutex> lock(mtx);
        numR--;
        if (numR==0)
        {
            cv.notify_all();
        }
        
    }
    
}

void write(){


    std::unique_lock<std::mutex> lock(mtx);
    while (numR!=0)
    {
        cv.wait(lock);
    }
    numW++;
    std::cout<<"Scrittore sta scrivendo"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    numW--;
    cv.notify_all();

}

int main(){
    int NR, NW;
    std::cout<<"Inserisci il numero di reader: ";
    std::cin>>NR;
    std::cout<<"Inserisci il numero di writer: ";
    std::cin>>NW;
    std::vector<std::thread> reader;
    std::vector<std::thread> writer;

    for (size_t i = 0; i < NR; i++)
    {
        reader.emplace_back(std::thread(read));
    }
    
    for (size_t i = 0; i < NW; i++)
    {
        writer.emplace_back(std::thread(write));
    }



    for(auto& w : writer){
        w.join();
    }   

    for(auto& r: reader){
        r.join();
    }
}



