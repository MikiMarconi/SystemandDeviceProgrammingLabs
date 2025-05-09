#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>

std::mutex cout_mtx;


class threadPool
{
    private:
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;

    public:
    threadPool(int numt){
        for (size_t i = 0; i < numt; i++)
        {
            threads.emplace_back([this]{
                while (true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        // Wait until a task is available or the pool is stopped
                        while (stop || tasks.empty())
                        {
                            cv.wait(lock);

                        }
                        
                        if (stop && tasks.empty()) {
                        return; // Exit the thread
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
                
            });
        }
        
    }

    void enqueue(std::function<void()> funz){
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (stop)
            {
                return;
            }
            
            tasks.emplace(funz);
        }
        cv.notify_one();
    }
        
    ~threadPool(){
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop=true;
            cv.notify_all();
        }

        cv.notify_all();

        for (std::thread& thread : threads) {
            thread.join(); 
        }
    }


};

void print_message(std::string message){
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << message << std::endl;
}

int main(int argc, char **argv){
    if(argc!=2){
        std::cerr << "ERROR: Argument error" << std::endl;
        return EXIT_FAILURE;
    }
    int n_threads=atoi(argv[1]);
    threadPool pool(n_threads);

    for(int i=0;i<n_threads;i++){
        pool.enqueue([i](){print_message(std::to_string(i));});
    }
    std::this_thread::sleep_for(std::chrono::seconds(30));
    return EXIT_SUCCESS;
}










