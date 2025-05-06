#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;


struct semaphore{
    mutex mtx;
    int counter;
    condition_variable cv;

    semaphore(int n){
        counter=n;
    }

    void signal(){
        unique_lock<mutex> lock(mtx);
        counter++;
        cv.notify_one();
    }

    void acquire(){
        unique_lock<mutex> lock(mtx);
        while (counter<=0)
        {
            cv.wait(lock);
        }
        counter--;
    }

};


int main(){

    semaphore s(2);

}


