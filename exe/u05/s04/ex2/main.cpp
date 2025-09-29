#include <condition_variable>
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <vector>

std::condition_variable cv;
std::mutex mtx;
int countthread=1;

int getrandomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int>(1, 2) (gen);
}

void add(int &var){

    {
        std::lock_guard<std::mutex> lock(mtx);
        var+= getrandomint();
        if(var>=15){
            cv.notify_one();
            return;
        }
        countthread++;
        if(countthread==5){
            cv.notify_one();
        }
    }

}

int main(){
    int var = 10;
    std::vector<std::thread> pool;

    for(size_t i = 0; i<5; i++){
        pool.emplace_back(std::thread(add, std::ref(var)));
    } 
    {
        std::unique_lock<std::mutex> lock(mtx);
        while(var<15 && countthread != 5){
            cv.wait(lock);
        }
    }
    for(auto &v: pool){
        v.join();
    }

    std::cout<<var<<" "<<countthread;
}
