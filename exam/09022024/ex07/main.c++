#include <iostream>
#include <mutex>
#include <random>
#include <condition_variable>
#include <vector>
#include <chrono>

const int N=5;
std::mutex mtx, mtx_stop;
bool stop=false;
std::condition_variable cv;

int getrandom(){
    static std:: random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int>(1, 10) (gen);
}

void appendint(std::vector<int>& vector){

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(getrandom()));

        {
            std::lock_guard<std::mutex> lock(mtx_stop);
            if (stop)
            {
                break;
            }
        
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            vector.emplace_back(getrandom());
            cv.notify_one();
        }
    }
}


int main(){

    std::vector<int> vector;
    std::vector<std::thread> pool;

    for (size_t i = 0; i < N; i++)
    {
        pool.emplace_back(std::thread(appendint, std::ref(vector)));
        
    }
    while(true){
        int sum=0;
        {        
            std::unique_lock<std::mutex> lock(mtx);
            while(sum<50){
                sum=0;
                cv.wait(lock);
                for(auto& val:vector){
                    sum+=val;
                }
            }
            {
                std::lock_guard<std::mutex> lock(mtx_stop);
                stop=true;
            }

        }
        
        break;
    }



    for(auto& t: pool){
        t.join();
    }

    for(auto& val: vector){
        std::cout<<val<<std::endl;
    }

}