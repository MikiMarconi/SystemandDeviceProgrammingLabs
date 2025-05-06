#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <condition_variable>
#include <cstdlib>
#include <ctime>

using namespace std;

mutex mtx;
condition_variable cv;
bool flag=false;

void initAndWait(int& var){
    unique_lock<mutex> lock(mtx);
    var=10;
    flag=true;
    cv.notify_all();

    while(var<15){
        cv.wait(lock);
    }

    cout<<"Risultato: "<<var;
    exit(0);

}

void add(int& var){

    unique_lock<mutex> lock(mtx);

    while(!flag){
        cv.wait(lock);
    } 

    int random = rand() % 2 + 1;
    var+=random;

    if(var>=15){
        cv.notify_all();
    }else{
        cv.notify_one();
    }

}


int main(){
    int var=0;
    thread admin(initAndWait, ref(var));
    thread adder1(add, ref(var));
    thread adder2(add, ref(var));
    thread adder3(add, ref(var));
    thread adder4(add, ref(var));
    thread adder5(add, ref(var));

    admin.join();
    adder1.join();
    adder2.join();
    adder3.join();
    adder4.join();
    adder5.join();
}