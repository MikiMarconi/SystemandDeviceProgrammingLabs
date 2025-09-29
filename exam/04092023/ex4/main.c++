#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include <string>

std::mutex mtx;

double determinant (std::vector<std::vector<double>> &matrix);

void readfileandwritedeterminant(std::string filename, int i){
    double det;
    std::vector<std::vector<double>> mat;

    std::ifstream file_text(filename);
    if(!file_text.is_open()){
        std::cerr<<"Error in file "<<filename<<std::endl;
    }

    std::string line;
    while(std::getline(file_text, line)){
        std::vector<double> row;
        std::istringstream iss(line);
        double val;
        while (iss>>val)
        {
            row.emplace_back(val);
        }
        mat.emplace_back(row);
    }

    file_text.close();
    det = determinant(std::ref(mat));
    consume(std::ref(det), std::ref(i));
}


void consume(double& det, int& i ){
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::ofstream out("FileOut.txt", std::ios::app);
        if(out.is_open()){
            out<<det<<" "<<i<<" ";
        }
    }
}

int main(){
    int N;
    int i;

    std::cout<<"value N: ";
    std::cin>>N;
    std::vector<std::thread> pool;
    
    for(i=0;i<N;i++){
        std::string filename = "fileIn-"+std::to_string(i)+".txt";
        pool.emplace_back(readfileandwritedeterminant, filename, i);
    }

    for(auto& v: pool){
        v.join();
    }

}