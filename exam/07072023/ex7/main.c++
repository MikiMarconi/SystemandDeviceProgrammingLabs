#include <iostream>
#include <thread>
#include <semaphore>
#include <random>

std::counting_semaphore<2> semA(2);
std::counting_semaphore<2> semBC(0);
std::counting_semaphore<2> semD(0);
std::mutex mtx;
int countA=0;
int countBC=0;
int random=0;

int randomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int>(2, 10) (gen);
}

void writeA(){
    while (true)
    {
        semA.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"A";
            countA++;
            if(countA==2){
                int i;
                random = randomint();
                for(i=0;i<random;i++){
                    semBC.release();
                }
            }
        }
    }
}

void writeB(){
    while (true)
    {
        semBC.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"B";
            countBC++;
            if(countBC==random){
                semD.release();
                semD.release();
            }
        }
    }    
}

void writeC(){
    while (true)
    {
        semBC.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"C";
            countBC++;
            if(countBC==random){
                semD.release();
                semD.release();
            }
        }

    }    
}

void writeD(){
    while (true)
    {
        semD.acquire();
        semD.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"DD"<<std::endl;
            countA=0;
            countBC=0;
            semA.release();
            semA.release();
        }

    }    
}

int main(int argc, char** argv){

    std::thread TA(writeA);
    std::thread TB(writeB);
    std::thread TC(writeC);
    std::thread TD(writeD);

    TA.join();
    TB.join();
    TC.join();
    TD.join();
}