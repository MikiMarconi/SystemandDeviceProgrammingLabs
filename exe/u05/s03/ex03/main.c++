#include <semaphore>
#include <thread>
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;

counting_semaphore<1> mut(1);  // Mutex globale per serializzare l'output sulla console

map<int, unique_ptr<binary_semaphore>> prioritysem; // Usato il puntatore perchè il semaforo non è copiabile

mutex cout_mutex; // Mutex per il controllo dell'output in console

void worker(int i, int priority) {
    // Locking per l'output sulla console
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Il thread " << i << " con priorita' " << priority << " e' in lock" << endl;
    }

    // Creazione del semaforo binario specifico per questo thread
    prioritysem.insert({priority, make_unique<binary_semaphore>(0)});

    // Attende il semaforo per poter proseguire
    (*prioritysem[priority]).acquire();

    // Locking per l'output sulla console
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Sblocco thread " << i << " con priorita' " << priority << endl;
    }
}

int main() {
    int i, priority;
    int n = 10;
    vector<thread> pool;

    // Creazione dei thread con priorità
    for (i = 0; i < n; i++) {
        priority = (i + 1) * 100;  // Priorità crescente
        pool.push_back(thread(worker, i, priority));
    }

    // Assicuriamo che i thread vengano sbloccati in ordine di priorità crescente
    i = 0;

    // Aspetta che tutti i worker abbiano inserito il proprio semaforo nella mappa
    while(prioritysem.size() < n) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    for (const auto &t : prioritysem) {
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Sbloccando thread " << i++ << " con priorita' " << t.first << endl;
        }
        (*(t.second)).release();  // Rilascia il semaforo del thread
    }

    // Attendi che tutti i thread finiscano
    for (i = 0; i < n; i++) {
        pool[i].join();
    }

    return 0;
}
