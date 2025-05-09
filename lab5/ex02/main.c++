#include <iostream>
#include <thread>
#include <mutex> 
#include <random>
#include <semaphore>
#include <vector>
#include <chrono>

std::mutex mtx;
bool stop=false;


int get_random_number(int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(min, max);
    return dis(gen);
}

void enterparking(int& available){
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (stop)
            {
                break;
            }
            
        }

        {        
            std::lock_guard<std::mutex> lock(mtx);

            if (available>0)
            {
                available--;
                std::cout<<"Macchina entrata posti disponibili: "<<available<<std::endl;
            }
            
        }

        std::this_thread::sleep_for(std::chrono::seconds(get_random_number(1,3)));
    }
    
}

void exitparking(int& available){
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (stop)
            {
                break;
            }
            
        }

        {        
            std::lock_guard<std::mutex> lock(mtx);

            if (available<5)
            {
                available++;
                std::cout<<"Macchina uscita posti disponibili: "<<available<<std::endl;
            }
            
        }

        std::this_thread::sleep_for(std::chrono::seconds(get_random_number(4,7)));
    }
}



int main(int argv, char **argc){

    int var=std::atoi(argc[1]);
    int numP = std::atoi(argc[2]);

    std::thread exitT(exitparking, std::ref(numP));
    std::thread enterT(enterparking, std::ref(numP));


    while (true)
    {
        std::this_thread::sleep_for (std::chrono::seconds(1));
        var--;
        if (var==0)
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop=true;
            break;
        }
        
    }

    exitT.join();
    enterT.join();

    
    return 0;
}