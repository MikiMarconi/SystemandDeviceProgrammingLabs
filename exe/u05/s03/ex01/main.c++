#include <iostream>
#include <thread>
#include <semaphore>  

using namespace std;

counting_semaphore<1> sem(1);
counting_semaphore<2> sem2(2);
counting_semaphore<1> mx(1);

int counter=0;
int counterb=0;

void stampaB() {
    while(true){
        sem2.acquire();
        mx.acquire();
        cout << "B";
        
        counter++;
        if(counter==3){
            cout<<endl;
            counter=0;
            sem2.release();
            sem2.release();
            sem.release();
        }
        mx.release();
    }
}

void stampaA() {
    while(true){
        sem.acquire();
        mx.acquire();
        cout << "A";
        counter++;
        if(counter==3){
            cout<<endl;
            counter=0;
            sem2.release();
            sem2.release();
            sem.release();
        }
        mx.release();

    }
}

int main() {

    thread TB(stampaB);
    thread TA(stampaA);

    TA.join();
    TB.join();

    return 0;
}
