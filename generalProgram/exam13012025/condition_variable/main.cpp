#include <random>
#include <iostream>
#include <thread>
#include <list>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::list<std::string> FA;
std::list<std::string> FB;
std::mutex mtx;
std::mutex mtxconsole;
std::condition_variable cv;
bool flagA = false;
bool flagB = false;


int getrandominterval(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (1, 10) (gen);
}

void produceFA(){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(getrandominterval()));
        {
            std::lock_guard<std::mutex> lock1(mtx);
            std::string st;
            {
                std::lock_guard<std::mutex> lock(mtxconsole);
                std::cout<<"insert element for FA: ";
                std::cin>>st;
            }
            FA.emplace_back(st);
            flagA = true;
            cv.notify_one();
        }
    }
}

void produceFB(){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(getrandominterval()));
        {    
            std::lock_guard<std::mutex> lock1(mtx);
            std::string st;
            {
                std::lock_guard<std::mutex> lock(mtxconsole);
                std::cout<<"insert element for FB: ";
                std::cin>>st;
            }
            FB.emplace_back(st);
            flagB = true;
            cv.notify_one();
        }        
    }
}

void consume(){
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while(!flagA || !flagB){
            cv.wait(lock);
        }
        std::string A = FA.front();
        std::string B = FB.front();
        {
            std::lock_guard<std::mutex> lock1(mtxconsole);
            std::cout<<A<<" "<<B<<std::endl;
        }
        flagA = false;
        flagB = false;
        if(A == "end" && B == "end"){
            FA.pop_front();
            FB.pop_front();
            std::cout<<"program terminates";
            exit(0);
        }
        FA.pop_front();
        FB.pop_front();
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