#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>

std::counting_semaphore<1> semA(1);
std::counting_semaphore<1> semBC(0);
std::counting_semaphore<1> semD(0);
std::counting_semaphore<1> semE(0);
std::mutex mtx;

int count=0;

void writeA(){
    while(true){
        semA.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(count==2){
                std::cout<<"A"<<std::endl;
                count=0;
            }
            std::cout<<"A";
            
        }
        semBC.release();
    }
}

void writeB(){
    while(true){
        semBC.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"-B";
        }
        semD.release();
        semE.release();
    }
}

void writeC(){
    while(true){
        semBC.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout<<"-C";
        }
        semE.release();
        semD.release();
    }
}

void writeD(){
    while(true){
        semD.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(count== 1){
                std::cout<<"D-";
            }else{
                std::cout<<"-D";
            }
            count++;

            if(count==2){
                semA.release();
            }
        }
    }
}

void writeE(){
    while(true){
        semE.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(count== 1){
                std::cout<<"E-";
            }else{
                std::cout<<"-E";
            }
            count++;

            if(count==2){
                semA.release();
            }
        }
    }
}

int main(){
    std::thread TA(writeA);
    std::thread TB(writeB);
    std::thread TC(writeC);
    std::thread TD(writeD);
    std::thread TE(writeE);


    TA.join();
    TB.join();
    TC.join();
    TD.join();
    TE.join();
}