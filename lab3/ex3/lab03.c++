#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <vector>

using namespace std;

struct friendship {
    string person1;
    string person2;
};

// Funzione DFS per trovare il percorso tra due persone
bool findConnectionDFS(const string& start, const string& target, 
                       map<string, set<string>>& mapfs, 
                       set<string>& visited, 
                       vector<string>& path) {
    // Aggiungi la persona al percorso
    visited.insert(start);
    path.push_back(start);

    // Se abbiamo trovato il target, ritorna true
    if (start == target) {
        return true;
    }

    // Esplora gli amici
    for (const string& friendName : mapfs[start]) {
        if (visited.find(friendName) == visited.end()) {  // Se non è stato visitato
            if (findConnectionDFS(friendName, target, mapfs, visited, path)) {
                return true;  // Se il percorso è trovato
            }
        }
    }

    // Rimuovi il nodo corrente dal percorso se non troviamo un percorso
    path.pop_back();
    return false;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nome_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file) {
        cerr << "Errore nell'apertura del file!" << endl;
        return 1;
    }

    map<string, set<string>> mapfs;
    friendship f;
    set<string> setfr;

    // Costruisci la rete sociale
    while (file >> f.person1 >> f.person2) {
        mapfs[f.person1].insert(f.person2);
        mapfs[f.person2].insert(f.person1);
        setfr.insert(f.person1);
        setfr.insert(f.person2);
    }

    file.close();

    // Stampa tutte le persone nella rete sociale
    cout << "Le persone nella rete sociale sono:" << endl;
    for (auto it = setfr.begin(); it != setfr.end(); ++it) {
        cout << *it << endl;
    }

    // Stampa la lista degli amici per ciascuna persona
    cout << "\nAmici di ogni persona:" << endl;
    for (const auto& entry : mapfs) {
        cout << entry.first << " ha come amici: ";
        for (const auto& friendName : entry.second) {
            cout << friendName << " ";
        }
        cout << endl;
    }

    // Chiedi all'utente di inserire due persone da verificare se sono connesse
    string person1, person2;
    cout << "\nInserisci il nome della prima persona: ";
    cin >> person1;
    cout << "Inserisci il nome della seconda persona: ";
    cin >> person2;

    // Verifica la connessione tra person1 e person2
    set<string> visited;
    vector<string> path;

    if (findConnectionDFS(person1, person2, mapfs, visited, path)) {
        // Se trovato il percorso, stampa la lista di amici
        cout << "Le persone " << person1 << " e " << person2 << " sono connesse!" << endl;
        cout << "Il percorso di amicizie che li collega e': ";
        for (const string& p : path) {
            cout << p << " ";
        }
        cout << endl;
    } else {
        cout << person1 << " e " << person2 << " non sono connessi nella rete." << endl;
    }

    return 0;
}
