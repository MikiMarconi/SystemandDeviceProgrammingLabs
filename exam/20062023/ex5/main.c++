#include <iostream>
#include <barrier>
#include <mutex>
#include <random>
#include <thread> 
#include <vector>

std::mutex mtx;
bool flag=true;

int generaterandomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (1, 10) (gen);
}

int n= generaterandomint();
std::barrier<> threadbarrier(n);

void work(){
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout<<"working..."<<std::endl;
    }
    threadbarrier.arrive_and_wait();
    {
        std::lock_guard<std::mutex> lock(mtx);
        flag=true;
    }
}

int main(){
    while (flag)
    {
        std::vector<std::thread> pool;
        int i;
        for(i=0; i<n; i++){
            pool.emplace_back(std::thread(work));
        }
        flag= false;
        for(auto& v: pool){
            v.join();
        }        
    }
    

}

