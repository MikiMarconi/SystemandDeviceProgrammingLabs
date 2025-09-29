#include <iostream>
#include <mutex>
#include <condition_variable>



class semaphore{
    private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

    public:
    semaphore(int counter){
        count = counter;
    }

    void acquire(){
        {
            std::unique_lock<std::mutex> lock(mtx);
            while(count==0){
                cv.wait(lock);
            }
            std::cout<<"Acquisito"<<std::endl;
            count--;
        }
    }

    void release(){
        {
            std::unique_lock<std::mutex> lock(mtx);
            count++;
            std::cout<<"Rilasciato"<<std::endl;
        }
        cv.notify_all();
    }
};

int main(){

    semaphore semA(2);
    semA.acquire();
    semA.acquire();
    semA.release();
    semA.acquire();
    return 0;
}