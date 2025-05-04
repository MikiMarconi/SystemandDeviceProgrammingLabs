#include <semaphore>
#include <thread>
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <mutex>
#include <random>

using namespace std;


int maxRank=0;

struct bestThread{
    std::thread::id id;
    int rank;
    int num_votes;
    mutex mtx;
};
bestThread* best;
counting_semaphore<10> barrier(0);

int randomRank(){

    // Generatore di numeri casuali
    static random_device rd;  // Dispositivo per generare numeri casuali
    static mt19937 gen(rd());  // Mersenne Twister per la generazione
    return uniform_int_distribution<int>(0, 1000) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}


void worker(int rank){
    best->mtx.lock();
    if(rank>best->rank){
        best->rank= rank;
        best->id= std::this_thread::get_id();
    }
    best->num_votes++;

    if(best->num_votes<10){
        cout<<"WAITING  id = "<< std::this_thread::get_id()<<" rank = "<< rank <<" leader id = "<<
        best->id<<" leader rank = "<< best->rank<<endl;
        best->mtx.unlock();
        barrier.acquire();
        best->mtx.lock();
        cout<<"RELEASE  id = "<< std::this_thread::get_id()<<" rank = "<< rank <<" leader id = "<<
        best->id<<" leader rank = "<< best->rank<<endl;
        best->mtx.unlock();
    }else{
        cout<<"LAST  id = "<< std::this_thread::get_id()<<" rank = "<< rank <<" leader id = "<<
        best->id<<" leader rank = "<< best->rank<<endl;
        best->mtx.unlock();
        for(int i =0; i<9; i++){
            barrier.release();
        }
    }
};

int main(){
    best = new bestThread();
    best->rank=0;
    best->num_votes=0;

    vector<thread> poolT;
    for (int i=0; i<10 ;i++){
        
        int rank = randomRank();
        poolT.emplace_back(thread(worker, rank));

    }

    for (auto& t : poolT) t.join();
    delete best;
    return 0; 
}

