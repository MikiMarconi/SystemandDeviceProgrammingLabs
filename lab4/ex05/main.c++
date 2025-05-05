#include <iostream>
#include <vector>
#include <random>

using namespace std;

double randomRank(){

    // Generatore di numeri casuali
    static random_device rd;  // Dispositivo per generare numeri casuali
    static mt19937 gen(rd());  // Mersenne Twister per la generazione
    return uniform_real_distribution<double>(-0.5, 0.5) (gen);  // Distribuzione per numeri casuali tra 1 e 1000
}

int main(){

    int n;
    cout<<"Inserisci n: "<<endl;
    cin>>n;

    
    vector<double> v1;
    vector<double> v2;
    vector<vector<double>> mat(n);

    for(int i=0; i<n; i++){
        v1.emplace_back(randomRank());
        v2.emplace_back(randomRank());
        
        for(int j=0; j<n; j++){
            
            mat[i].emplace_back(randomRank());
        }
    }

    double res=0;

    for(int i=0; i<n; i++){
        double tmp=0;
        for(int j=0; j<n; j++){
            tmp=v1[j]*mat[j][i];    
        }
        res+=tmp*v2[i];
    }

    cout<<res<<endl;
}