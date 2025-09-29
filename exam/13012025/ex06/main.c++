#include <random>
#include <iostream>
#include <mutex>
#include <future>
#include <chrono>

std::string molecule;

int randomval(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int>(1, 10)(gen);
}

void produceH(std::promise<char>& pr){
    std::this_thread::sleep_for(std::chrono::seconds(randomval()));

    pr.set_value('H');
}

void produceH2(std::promise<char>& pr){
    std::this_thread::sleep_for(std::chrono::seconds(randomval()));

    pr.set_value('H');
}

void produceO(std::promise<char>& pr){
    std::this_thread::sleep_for(std::chrono::seconds(randomval()));

    pr.set_value('O');
}

void produceH2O(std::future<char>& fh1, std::future<char>& fh2, std::future<char>& fo){

    std::cout<<fh1.get()<<" "<<fh2.get()<<" "<<fo.get()<<std::endl;

    std::cout<<"H2O";
}

int main(){

    std::future<char> futh1;
    std::promise<char> promh1;
    std::future<char> futh2;
    std::promise<char> promh2;
    std::future<char> futo;
    std::promise<char> promo;

    futh1 = promh1.get_future();
    futh2 = promh2.get_future();
    futo = promo.get_future();


    std::thread th1(produceH, std::ref(promh1));
    std::thread th2(produceH2, std::ref(promh2));
    std::thread to(produceO, std::ref(promo));
    std::thread th2o(produceH2O, std::ref(futh1), std::ref(futh2), std::ref(futo));


    th1.join();
    th2.join();
    to.join();
    th2o.join();



}