#include <iostream>
#include <vector>
#include <random>
#include <condition_variable>
#include <mutex>
#include <thread>

std::vector<int> buffer;
std::condition_variable cv;
std::mutex mtxbuffer;
std::mutex mtxconsole;
int buffersize = 0;

int getrandomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (-100, 100) (gen);
}

void produce(){

    {
        std::lock_guard<std::mutex> lock(mtxbuffer);
        for(size_t i=0; i<5; i++){
            buffersize++;
            int val = getrandomint();
            buffer.emplace_back(val);
            {
                std::lock_guard<std::mutex> lock2(mtxconsole);
                std::cout<<"Produced value: "<<val<<std::endl;
            }
        }
    }
    cv.notify_all();

}

void consume(){
    std::unique_lock<std::mutex> lock(mtxbuffer);
    while(buffersize<3){
        cv.wait(lock);
    }
    for(size_t i=0; i<3; i++){
        buffersize--;
        {
            std::lock_guard<std::mutex> lock2(mtxconsole);
            std::cout<<"Consumed value: "<<buffer.back()<<std::endl;
        }
        buffer.pop_back();
    }

}

int main(int argc, char** argv){

    int NP = std::atoi(argv[1]);
    int NC = std::atoi(argv[2]);
    std::vector<std::thread> poolproducer;
    std::vector<std::thread> poolconsumer;

    for(size_t i=0; i<NP; i++){
        poolproducer.emplace_back(std::thread(produce));
    }

    for(size_t i=0; i<NC; i++){
        poolconsumer.emplace_back(std::thread(consume));
    }

    for(auto& val: poolproducer){
        val.join();
    }

    for(auto& val: poolconsumer){
        val.join();
    }


}