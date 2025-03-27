#include <iostream>
#include <string>  
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;


int main(int argc, char **argv){

    if(argc!=2){
        cerr<<"argument error";
        return EXIT_FAILURE;
    }

    string name;
    bool trovato=false;
    list<int> listanum; 
    map<string, list<int>> mappa;
    int num;

    ifstream file_text(argv[1]);

    if (!file_text.is_open()) {
        cerr << "Errore nell'apertura del file di testo" << endl;
        return EXIT_FAILURE;
    }

    

    while(file_text>>name){
        listanum.clear();

        while(file_text>> num){
            listanum.push_back(num);
            if (file_text.peek() == '\n' || file_text.peek() == EOF) {
                break;  // Esci dal ciclo quando raggiungi la fine della riga o un nuovo nome
            }
        }
        for(auto& item: mappa){
            if(item.first == name){
                trovato =true;
                item.second.insert(item.second.end(), listanum.begin(), listanum.end());    
            }
        }
        if(!trovato){
            mappa.insert({name, listanum});
        }
    }

    for (const auto &w : mappa) {
        cout << w.first << " " ;
        for(const auto &j : w.second){
            cout<<j<<" ";
        } 
        cout<<endl;
    }
    file_text.close();
    return EXIT_SUCCESS;
}