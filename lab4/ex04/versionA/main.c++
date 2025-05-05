#include <iostream>
#include <fstream>
#include <thread>
#include <semaphore>
#include <list>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Punto Iniziale
auto start = high_resolution_clock::now();

mutex mtx;
int totNum=0;

struct record{
    int numVal;
    list<int> listInt;
};

record r;

void mapfile(string filename){
    ifstream file(filename);

    if(!file.is_open()){
        mtx.lock();
        cerr<< "File error"<< filename << endl;
        mtx.unlock();
    }else{

        mtx.lock();
        int val=0;
        bool first = true;

        while(file>>val){
            if (first)
            {
                totNum+=val;
                r.numVal=totNum;
                first=false; 
            }else{
                r.listInt.emplace_back(val);
            }
            //r.listInt.sort(); //ordina in modo crescente per decrescente usare .sort(grater<int>())
            
        }
        mtx.unlock();
    }
}

int main(int argc, char **argv){

    if(argc!=5){
        cerr<<"Argument error"<<endl;
        return EXIT_FAILURE;
    }

    thread t1(mapfile, argv[1]);
    thread t2(mapfile, argv[2]);
    thread t3(mapfile, argv[3]);

    t1.join();
    t2.join();
    t3.join();
    
    ofstream out(argv[4]);
    if (!out.is_open()) {
        cerr << "Errore apertura file output: " << argv[4] << endl;
        return EXIT_FAILURE;
    }
    r.listInt.sort();
    out<<r.numVal<<" ";
    for(int v : r.listInt){
        out<<v<<" ";
    }

    // Punto finale
    auto stop = high_resolution_clock::now();

    // Calcola la durata in millisecondi
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Tempo impiegato: " << duration.count() << " microseconds" << endl;


}


