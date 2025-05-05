#include <iostream>
#include <vector>
#include <random>
#include <thread>

using namespace std;
int counter=0;
double res=0;
mutex mtx;

double randomRank(){

    // Generatore di numeri casuali
    static random_device rd;  // Dispositivo per generare numeri casuali
    static mt19937 gen(rd());  // Mersenne Twister per la generazione
    return uniform_real_distribution<double>(-0.5, 0.5) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}

void worker(int i, const vector<double>& v1, vector<double>& v, const vector<vector<double>>& mat, const vector<double>& v2, int n){

        double sum = 0;
        for (int j = 0; j < v1.size(); ++j) {
            sum += v1[j] * mat[i][j];  // prodotto scalare della riga i-esima con v1
        }
        v[i] = sum;
        bool last= false;
        mtx.lock();
        counter++;
        if(counter==n){
            last=true;
        }
        mtx.unlock();

    if(last){
        for(int i=0; i<n; i++){
            res+=v[i]*v2[i];
        }
        cout<<res<<endl;
    }

}

int main(){

    int n;
    cout<<"Inserisci n: "<<endl;
    cin>>n;

    
    vector<double> v1(n);
    vector<double> v2(n);
    vector<double> v(n);
    vector<vector<double>> mat(n, vector<double>(n));



    for(int i=0; i<n; i++){
        v1[i] = randomRank();
        v2[i] = randomRank();
        
        for(int j=0; j<n; j++){
            
            mat[i][j] = randomRank();
        }
    }

    vector<thread> pool;

    for(int i=0; i<n; i++){
        pool.emplace_back(worker, i, cref(v1), ref(v), cref(mat), cref(v2), n);
    }


    for(auto &t : pool){
        t.join();
    }



}