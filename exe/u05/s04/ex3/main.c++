#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <semaphore>

std::vector<int> v;
bool flag=true;
std::condition_variable cv;
int command;
std::mutex mtx;
int index=0;


void writerfun(){
    while (true)
    {
        int random = rand()%10+1;
        mtx.lock();
        v.push_back(random);
        mtx.unlock();
        index++;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void uifun(){
    while (true)
    {
        mtx.lock();
        std::cout<<"Inserisci comando: ";
        mtx.unlock();
        std::cin>>command;
        flag=false;
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
}

void work(){
    while (true)
    {
        while(flag){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock);
        }

        flag=true;
        switch (command)
        {
        case 0:
            exit(0);
            break;
        case 1:
            mtx.lock();
            for (auto elem : v)
            {
                std::cout<<elem<<std::endl;
            }
            mtx.unlock();
            break;
        case 2:
            mtx.lock();
            std::cout<<v[index-1]<<std::endl;
            mtx.unlock();
            break;
        case 3:
            mtx.lock();
            v.clear();
            index=0;
            mtx.unlock();
            break;
        default:
            break;
        }


    }
}

int main(){
    std::thread writer(writerfun);
    std::thread ui(uifun);
    std::thread worker(work);

    writer.join();
    ui.join();
    worker.join();
}




