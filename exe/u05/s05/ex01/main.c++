#include <semaphore>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

std::mutex mtx;
int counter=0;
bool flag=true;
std::counting_semaphore<0> sem(0);


void work(int& numT){

    mtx.lock();    
    std::cout<<"inizio lavoro"<<std::endl;
    counter++;
    flag=(counter==numT);
    mtx.unlock();
    if (!flag)
    {
        sem.acquire();
    }else{
        for (size_t i = 0; i < numT-1; i++)
        {
            sem.release();
        }
    }
    mtx.lock();
    std::cout<<"Lavoro terminato"<<std::endl;
    mtx.unlock();

}


int main(){

    int numT;
    std::cout<<"Quanti thread vuoi creare?"<<std::endl;
    std::cin>>numT;
    std::vector<std::thread> pool;


    for (size_t i = 0; i < numT; i++)
    {
        pool.emplace_back(std::thread(work, std::ref(numT)));
    }

    for(auto& t :pool){
        t.join();
    }

}



