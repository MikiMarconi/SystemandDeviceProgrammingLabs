#include <iostream>
#include <thread>
#include <semaphore>
#include <random>
#include <mutex>
std::mutex mtx;
std::counting_semaphore<1> semCD(0);
int randomint(){
static std::random_device rd;
static std::mt19937 gen(rd());
return std::uniform_int_distribution<int> (1, 10) (gen);
}
void printA(){
while(true){
std::lock_guard<std::mutex> lock(mtx);
for(size_t i=0; i<randomint(); i++){
std::cout<<"A";
}
semCD.release();
}
}
void printB(){
while(true){
std::lock_guard<std::mutex> lock(mtx);
for(size_t i=0; i<randomint(); i++){
std::cout<<"B";
}
semCD.release();
}
}
void printC(){
while(true){
semCD.acquire();
{
std::lock_guard<std::mutex> lock(mtx);
std::cout<<"C"<<std::endl;
}
}
}
void printD(){
while(true){
semCD.acquire();
{
std::lock_guard<std::mutex> lock(mtx);
std::cout<<"D"<<std::endl;
}
}
}
int main(){
std::thread TA(printA);
std::thread TB(printB);
std::thread TC(printC);
std::thread TD(printB);
TA.join();
TB.join();
TC.join();
TD.join();
}