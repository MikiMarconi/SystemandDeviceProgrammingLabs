#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <barrier>


std::vector<std::vector<double>> A(10);
std::vector<double> x(10);
std::vector<double> b(10);
std::vector<double> x_new(10);
std::barrier<> barriera(10);

int randomval(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_real_distribution<double>(-10, 10) (gen);

}


void threadjacobi (std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x, std::vector<double>& x_new, int n, int i, int k){

    for (size_t it = 0; it < k; it++)
    {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                sum += A[i][j] * x[j];
            }
        }

        x_new[i] = 1 / A[i][i] * (b[i]- sum);

        barriera.arrive_and_wait();

        std::swap(x,x_new);

        barriera.arrive_and_wait();
    }
    

}

void jacobi (std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x, std::vector<double>& x_new, int n){
    
    std::vector<std::thread> pool;
    int k=10;

    for (size_t i = 0; i < n; i++)
    {
        pool.emplace_back(std::thread(threadjacobi, std::ref(A), std::ref(b), std::ref(x), std::ref(x_new), 10, i, k));
    }
    
    for(auto& t : pool){
        t.join();
    }

    

 }


int main(){

    for (size_t i = 0; i < 10; i++)
    {
        x.emplace_back(randomval());
        b.emplace_back(randomval());

        for(size_t j =0; j<10; j++){

            A[i].emplace_back(randomval());

        }
    }

    jacobi(std::ref(A), std::ref(b), std::ref(x), std::ref(x_new), 10);


    for(auto& t : x_new){
        std::cout<<t<<std::endl;
    }

    return 0; 
}