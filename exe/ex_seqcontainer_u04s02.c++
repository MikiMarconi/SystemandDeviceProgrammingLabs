#include <iostream>
#include <string>  
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct element{
    string name;
    vector<int> vect;

    public: 
    bool push(){
        return islower(name[0]);
    }

};

void checkList(element e, list<element>& l){
    bool trovato= false;
    if(l.empty()){
        l.push_back(e);
    }else{
        for(auto& item: l){
            if(item.name == e.name){
                trovato =true;
                item.vect.insert(item.vect.end(), e.vect.begin(), e.vect.end());    
            }
        }
        if(!trovato){
            if(e.push()){
                l.push_front(e);
            }else{

                l.push_back(e);
            }
        }
    }
}

int main(int argc,char **argv){

    if(argc!=2){
        cerr<<"argument error";
        return EXIT_FAILURE;
    }

    ifstream file_text(argv[1]);

    if (!file_text.is_open()) {
        cerr << "Errore nell'apertura del file di testo" << endl;
        return EXIT_FAILURE;
    }

    element line;
    int num;
    list<element> listaelementi;

    while(file_text>>line.name){
        line.vect.clear();

        while(file_text>> num){
            line.vect.push_back(num);
            if (file_text.peek() == '\n' || file_text.peek() == EOF) {
                break;  // Esci dal ciclo quando raggiungi la fine della riga o un nuovo nome
            }
        }
        checkList(line, listaelementi);
    }

    file_text.close();

    cout << "Contenuto della lista:" << endl;
    for (const auto& elem : listaelementi) {
        cout << "Nome: " << elem.name << " | Numeri: ";
        for (int num : elem.vect) {
            cout << num << " ";
        }
        cout << endl;
    }

    return  EXIT_SUCCESS;

}