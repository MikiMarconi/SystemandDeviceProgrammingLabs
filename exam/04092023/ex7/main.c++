#include <iostream>
#include <future>
#include <thread>

void orfun(bool l1, bool l2, std::promise<bool>& p){

    if(l1 || l2){
        p.set_value(true);
    }else{
        p.set_value(false);
    }

}

void andfun(bool l1, bool l2, std::promise<bool>& p){

    if(l1 && l2){
        p.set_value(true);
    }else{
        p.set_value(false);
    }

}

int main(){
    bool l1 = true;
    bool l2 = true;
    bool l3 = true;
    bool l4 = true;
    bool l5 = true;
    bool l6 = true;
    bool l7 = true;
    bool l8 = true;

    std::promise<bool> p1, p2, p3, p4, p5, p6, p7;
    std::future<bool> fut1 = p1.get_future();
    std::future<bool> fut2 = p2.get_future();
    std::future<bool> fut3 = p3.get_future();
    std::future<bool> fut4 = p4.get_future();
    std::future<bool> fut5 = p5.get_future();
    std::future<bool> fut6 = p6.get_future();
    std::future<bool> fut7 = p7.get_future();
    
    std::thread Tand1(andfun, l1, l2, std::ref(p1));
    std::thread Tand2(andfun, l3, l4, std::ref(p2));
    std::thread Tand3(andfun, l5, l6, std::ref(p3));
    std::thread Tand4(andfun, l7, l8, std::ref(p4));

    std::thread Tor1(orfun, fut1.get(), fut2.get(), std::ref(p5));
    std::thread Tor2(orfun, fut3.get(), fut4.get(), std::ref(p6));

    std::thread Tand5(andfun, fut5.get(), fut6.get(), std::ref(p7));

    Tand1.join();
    Tand2.join();
    Tand3.join();
    Tand4.join();
    Tand5.join();
    Tor1.join();
    Tor2.join();

    std::cout<<"Result: "<< fut7.get();
}