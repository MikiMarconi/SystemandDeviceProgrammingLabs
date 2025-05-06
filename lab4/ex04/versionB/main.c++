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

list<list<int>> mat;

void mapfile(string filename){
    ifstream file(filename, ios::binary);

    if(!file.is_open()){
        mtx.lock();
        cerr<< "File error"<< filename << endl;
        mtx.unlock();
    }

    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(int)); // legge quanti valori ci sono

    list<int> localList;

    for(int j = 0; j < count; ++j){
        int val;
        file.read(reinterpret_cast<char*>(&val), sizeof(int));
        localList.emplace_back(val);
        localList.sort();
    }

    file.close();

    lock_guard<mutex> lock(mtx);
    mat.push_back(localList);
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
    
    list<int> merged;
    for (auto& lst : mat) {
        merged.insert(merged.end(), lst.begin(), lst.end());
    }

    merged.sort();

    int total = merged.size();

    ofstream out(argv[4], ios::binary);
    if (!out.is_open()) {
        cerr << "Errore apertura file output: " << argv[4] << endl;
        return EXIT_FAILURE;
    }

    out.write(reinterpret_cast<char*>(&total), sizeof(int));
    
    // Scrive tutti gli interi
    for(int v : merged){
        out.write(reinterpret_cast<char*>(&v), sizeof(int));
    }

    // Punto finale
    auto stop = high_resolution_clock::now();

    // Calcola la durata in millisecondi
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Tempo impiegato: " << duration.count() << " microseconds" << endl;


}


