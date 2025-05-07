#include <iostream>
#include <thread>
#include <barrier>
#include <mutex>
#include <vector>

std::mutex mtx;
static std::vector<int> vettore = {5, 6, 2, 3 ,9 ,10, 22, 1, 12, 15};
std::barrier<> barrier(9);
bool all_ok = true;
bool sorted=true;

void swap(int i){
    while (sorted)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (vettore[i]<vettore[i+1])
            {
                
                int tmp= vettore[i];
                vettore[i]=vettore[i+1];
                vettore[i+1]=tmp;
                all_ok=false;

            }
            
        }
        barrier.arrive_and_wait();
        if(i==0){
            if(all_ok){
                sorted=false;
            }else{
                all_ok=true;
            }
        }
        barrier.arrive_and_wait();
    }
   
}

int main(){

    std::vector<std::thread> pool;

    for(int i =0; i<9; i++){
        pool.emplace_back(std::thread(swap, i));
    }

    for (auto& t : pool) {
        t.join();
    }

    for(auto& val : vettore){
        std::cout<<val<<std::endl;
    }

    return 0;

}