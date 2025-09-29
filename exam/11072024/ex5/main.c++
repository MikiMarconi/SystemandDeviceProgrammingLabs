#include <iostream>
#include <thread>
#include <future> 
#include <random>
#include <chrono>
#include <mutex>

std::mutex mtx;
bool flag= false;

int sum=0;
int prod=0;
int count=0;
int countcons=0;

int randomintval(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (1, 5) (gen);
}

float randomfloatval(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_real_distribution<float> (-1.0, 2.0) (gen);
}

void produce(std::promise<float>& val){     
    std::this_thread::sleep_for(std::chrono::seconds(randomintval()));
    float value= randomfloatval();
    val.set_value(value);
}

void consume_sum(std::shared_future<float>& fut1, std::shared_future<float>& fut2){
    float sum= fut1.get()+fut2.get();
    std::cout<<sum<<std::endl;
    if(sum==0){
        flag=true;
    }
}
void consume_prod(std::shared_future<float>& fut1, std::shared_future<float>& fut2){
    float prod= fut1.get()*fut2.get();
    std::cout<<prod<<std::endl;
    if(prod==0){
        flag=true;
    }
}

int main(){
    while(!flag){
        std::promise<float> val1, val2;
        std::shared_future<float> fut1 = val1.get_future().share();
        std::shared_future<float> fut2 = val2.get_future().share();

        std::thread consumer1(consume_sum, std::ref(fut1), std::ref(fut2));
        std::thread consumer2(consume_prod, std::ref(fut1), std::ref(fut2));
        std::thread producer1(produce, std::ref(val1));
        std::thread producer2(produce, std::ref(val2));

        producer1.join();
        producer2.join();
        consumer1.join();
        consumer2.join();
    }


}