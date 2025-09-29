#include <iostream>
#include <barrier>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>
#include <mutex>

std::mutex mtx_console;

int getrandompositive(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (0, 30) (gen);
}

int getrandomnumber(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (-100, 100) (gen);
}

const int N = getrandompositive();
std::barrier bar(N);

void work(){
    int size = getrandompositive();
    std::vector<int> vect(size);
    for(size_t i=0; i<size; i++){
        vect[i] = getrandomnumber();
    }
    bar.arrive_and_wait();
    std::sort(vect.begin(), vect.end());
    bar.arrive_and_wait();
    bool correct= true;
    for(size_t i=0; i<size-1; i++){
        
        if(vect[i]>vect[i+1]){
            correct = false;
        }
        
    }

    {
        std::lock_guard<std::mutex> lock(mtx_console);
        std::cout<<"Result: "<<correct<<std::endl;
    }
    bar.arrive_and_wait();

}

int main(){
    std::vector<std::thread> pool;

    for(size_t i=0; i<N; i++){
        pool.emplace_back(std::thread(work));
    }

    for(auto& v: pool){
        v.join();
    }

}