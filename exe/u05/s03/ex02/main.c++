#include <iostream>
#include <semaphore>
#include <thread>

using namespace std;

counting_semaphore<1> semTP(1);
counting_semaphore<1> semTM(0);
counting_semaphore<1> semTS(0);
counting_semaphore<1> semTNL(0);



void tplus(int n){
    while (true)
    {
        int tmp =  n; 
        semTP.acquire();
        while(tmp>0){
            cout<< "+";
            tmp--; 
        }
        semTNL.release();
    }
}


void tminus(int n){
    while (true)
    {
        int tmp =  n; 
        semTM.acquire();

        while(tmp>0){
            cout<< "-"; 
            tmp--;
        }
        semTNL.release();
    }
}

void star(int n){
    while(true){
        int tmp =  n; 
        semTS.acquire();

        while(tmp>0){
            cout<< "*";
            tmp--; 
        }
        semTNL.release();
    }
}


void newline(){
    int count=0;
    while (true)
    {
        semTNL.acquire();
        cout<< endl;
        count++;
        if(count%3==0){
            semTP.release();
        }
        if(count%3==1){
            semTM.release();
        }
        if(count%3==2){
            semTS.release();
        }
    }

}


int main(){

    int num=0;
    cout<<"inserisci il numero di caratteri da stampare:";
    cin >> num; 
    thread TP(tplus, num);
    thread TM(tminus, num);
    thread TS(star, num);
    thread TNL(newline);


    TP.join();
    TM.join();
    TS.join();
    TNL.join();

}