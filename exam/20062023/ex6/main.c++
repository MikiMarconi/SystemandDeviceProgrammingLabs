#include <future>
#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <cctype>   

void to_uppercase(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
}

void readstring(std::promise<std::string>& p1){
    std::string stringthread;
    std::cin>>stringthread;
    p1.set_value(stringthread);

}


void transformcapital(std::future<std::string>& fut, std::promise<std::string>& p){
    std::string stringt = fut.get();
    to_uppercase(stringt);
    p.set_value(stringt);

}

void showstring(std::future<std::string>& fut){
    std::cout<<fut.get();

}

int main(){
    
    std::promise<std::string> p1, p2;
    std::future<std::string> fut1= p1.get_future();
    std::future<std::string> fut2= p2.get_future();
    std::thread t1(readstring, std::ref(p1));
    std::thread t2(transformcapital, std::ref(fut1), std::ref(p2));
    std::thread t3(showstring, std::ref(fut2));

    t1.join();
    t2.join();
    t3.join();
}