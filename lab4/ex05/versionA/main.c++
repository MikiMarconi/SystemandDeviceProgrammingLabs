#include <iostream>
#include <vector>
#include <random>
#include <thread>

using namespace std;

double randomRank() {
    // Generatore di numeri casuali
    static random_device rd;  // Dispositivo per generare numeri casuali
    static mt19937 gen(rd());  // Mersenne Twister per la generazione
    return uniform_real_distribution<double>(-0.5, 0.5)(gen);  // Distribuzione per numeri casuali tra -0.5 e 0.5
}

void worker(int i, const vector<double>& v1, vector<double>& v, const vector<vector<double>>& mat) {
    double sum = 0;
    for (int j = 0; j < v1.size(); ++j) {
        sum += v1[j] * mat[i][j];  // prodotto scalare della riga i-esima con v1
    }
    v[i] = sum;  // Assegna il risultato alla posizione corretta di v
}

int main() {
    int n;
    cout << "Inserisci n: " << endl;
    cin >> n;

    vector<double> v1(n);  // Inizializza v1 con n elementi
    vector<double> v2(n);  // Inizializza v2 con n elementi
    vector<double> v(n);   // Inizializza v con n elementi
    vector<vector<double>> mat(n, vector<double>(n));  // Inizializza la matrice mat con dimensioni n x n

    // Popolamento delle variabili con valori casuali
    for (int i = 0; i < n; ++i) {
        v1[i] = randomRank();  // Assegna un valore casuale a v1[i]
        v2[i] = randomRank();  // Assegna un valore casuale a v2[i]
        for (int j = 0; j < n; ++j) {
            mat[i][j] = randomRank();  // Assegna un valore casuale alla matrice mat[i][j]
        }
    }

    vector<thread> pool;

    // Creazione dei thread
    for (int i = 0; i < n; ++i) {
        pool.emplace_back(worker, i, cref(v1), ref(v), cref(mat));  // Passa anche l'indice i
    }

    // Attendi che tutti i thread finiscano
    for (auto& t : pool) {
        t.join();
    }

    // Calcolo del risultato finale
    double res = 0;
    for (int i = 0; i < n; ++i) {
        res += v[i] * v2[i];  // Calcola il prodotto scalare di v e v2
    }

    cout << res << endl;
    return 0;
}
