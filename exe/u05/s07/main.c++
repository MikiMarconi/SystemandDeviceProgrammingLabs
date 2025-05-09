#include <thread>
#include <iostream>
#include <future>
#include <mutex>
#include <cmath>

bool is_prime(int n) {
    if (n < 2)
        return false;
    if (n == 2 ||  n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i <= sqrt(n); i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

void takefun(std::promise<int>& p){

    int n;
    std::cout<<"Inserisci il valore: ";
    std::cin>>n;

    p.set_value(n);

}


void checkfun(std::future<int>& fut, std::promise<bool>& prom){
    bool res = is_prime(fut.get());
    prom.set_value(res);
}


void givefun(std::future<bool>& fut){
    if(fut.get()){
        std::cout<<"Il numero e' primo!"<<std::endl;
    }else{
        std::cout<<"Il numero non e' primo!"<<std::endl;
    }

}



int main(){
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::promise<bool> prombool;
    std::future<bool> futbool = prombool.get_future();

    std::thread take(takefun, std::ref(prom));
    std::thread check(checkfun, std::ref(fut), std::ref(prombool));
    std::thread give(givefun, std::ref(futbool));



    check.join();
    give.join();
    take.join();

    return 0;
}
