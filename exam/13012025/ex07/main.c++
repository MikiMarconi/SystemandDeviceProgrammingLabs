#include <iostream>
#include <string>
#include <condition_variable>
#include <mutex>
#include <random>
#include <chrono>
#include <thread>
#include <queue>

std::mutex mtx_stdinput, mtx_count, mtx_stop;
std::condition_variable cv;
std::queue<std::string> FA;
std::queue<std::string> FB;
int countfa=0;
bool stop=false;
int countfb=0;


int randomval(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int>(1,10)(gen);
}

void produceFA(){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(randomval()));


        {
            std::lock_guard<std::mutex> lock(mtx_stdinput);
                {
                    std::unique_lock<std::mutex> lock(mtx_stop);
                    if(stop){
                        return;
                    }
                }
            std::string stringa;
            std::cout<<"inserisci stringa da inserire in FA: ";
            std::cin>>stringa;
            FA.emplace(stringa);
        }


        mtx_count.lock();
        countfa++;
        mtx_count.unlock();
        cv.notify_one();

    }

}


void produceFB(){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(randomval()));



        {
            std::lock_guard<std::mutex> lock(mtx_stdinput);
                {
                    std::unique_lock<std::mutex> lock(mtx_stop);
                    if(stop){
                        return;
                    }
                }   
            std::string stringa;
            std::cout<<"inserisci stringa da inserire in FB: ";
            std::cin>>stringa;
            FB.emplace(stringa);

        }
        mtx_count.lock();
        countfb++;
        mtx_count.unlock();
        cv.notify_one();
    }
    
}

void consume(){
    while(true){
        {
            std::unique_lock<std::mutex> lock(mtx_count);
            while (countfa==0 || countfb==0)
            {
                cv.wait(lock);
            }
        }
        
        {
            std::lock_guard<std::mutex> lock(mtx_stdinput);
                
            {
                std::lock_guard<std::mutex> lock(mtx_stop);
                if(FA.front()=="end" && FB.front()=="end"){
                    stop=true;
                    break;
                }
            }
            std::cout<<FA.front()<<" "<<FB.front()<<std::endl;
            FA.pop();
            FB.pop();
            mtx_count.lock();
            countfa--;
            countfb--;
            mtx_count.unlock();
        }
    }

}

int main(){
    std::thread P1(produceFA);
    std::thread P2(produceFB);
    std::thread C(consume);
    
    P1.join();
    P2.join();
    C.join();
    
}


