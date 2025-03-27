#include <iostream>
#include <string>  
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm> // Per remove_if()
#include <cctype>    // Per ispunct()

using namespace std;

void remover(string &w){
    //any_of() → Ritorna true se almeno un carattere è di punteggiatura.
    //::ispunct → È una funzione della libreria <cctype> 
    //che verifica se un carattere è un segno di punteggiatura (ad es. , . ! ? ;).
    //s.begin() e s.end() → Definiscono l'intervallo in cui cercare.
    if(any_of(w.begin(), w.end(), ::ispunct)){
        // remove_if() sposta i caratteri di punteggiatura alla fine della stringa,
        // e restituisce un iteratore alla nuova fine della stringa senza punteggiatura.
        // erase() poi rimuove fisicamente i caratteri non desiderati.
        w.erase(remove_if(w.begin(), w.end(), ::ispunct), w.end());
    }
}

int main(int argc, char **argv){

    if(argc!=2){
        cerr<<"argument error";
        return EXIT_FAILURE;
    }

    map<string, int> wordcount;
    set<string> chiavi;
    string word;
    int count=0;
    string find;

    ifstream file_text(argv[1]);

    if (!file_text.is_open()) {
        cerr << "Errore nell'apertura del file di testo" << endl;
        return EXIT_FAILURE;
    }

    while(file_text>>word){
        remover(word);

        //parola.begin() e parola.end() definiscono l'intervallo da modificare.
        //parola.begin() come terzo parametro indica dove salvare il risultato (cioè la stessa stringa).
        //::tolower converte ogni carattere in minuscolo.
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        ++wordcount[word];
        chiavi.insert(word);

    }

    for (const auto &w : wordcount) {
        cout << w.first << " occurs "  << w.second << endl; 
        count++;
    }
    cout<<"Numero di parole uniche: "<< count << endl;

    
    cout<<"Inserisci una parola da ricercare: ";
    cin>>find;

    auto iterator=wordcount.find(find);

    if(iterator!= wordcount.end()){
        cout<<"Parola trovata: "<< iterator->first<<" Conteggio: "<< iterator->second<<endl;
    }else{
        cout<<"Parola non trovata"<<endl;
    }

    for(auto &i: chiavi){
        cout<<i<<endl;
    }

    file_text.close();
    return EXIT_SUCCESS;
}