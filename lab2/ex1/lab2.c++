#include <iostream>
#include <string>  
#include <fstream>

using namespace std;

struct line{
    int num_row;
    long num_reg;
    char surname[29];
    char name[29];
    int mark;
};




int main() {
    char file_1[50];
    char file_2[50];
    char file_3[50];

    cin >> file_1;
    cin >> file_2;
    cin >> file_3;
    ifstream file_text(file_1); //apertura del file e lettura in binario
    ofstream file_binary(file_2, ios::binary);


    if (!file_text.is_open()) {
        cerr << "Errore nell'apertura del file di testo: " << file_1 << endl;
        return EXIT_FAILURE;
    }

    if (!file_binary.is_open()) {
        cerr << "Errore nell'apertura del file binario: " << file_2 << endl;
        return EXIT_FAILURE;
    }



    line l;

    /*tramite la condizione del while vado ad inserire le linee del file 
    all'interno della struct, in seguito vado a fare il cast dell'indirizzo 
    della struct ad char in modo tale che posso leggere e lavorare in byte
    il sizeOf fornisce la lunghezza in byte della struct line in modo tale da
    indicare quanti byte dovrà andare a scrivere*/
    while(file_text>> l.num_row >> l.num_reg >> l.surname >> l.name >> l.mark){
        file_binary.write(reinterpret_cast<char*>(&l), sizeof(line));
    }
    
    file_binary.close();
    file_text.close();

    ifstream file_binary_read(file_2, ios::binary);
    ofstream file_text_3(file_3, ios::out);

    if (!file_binary_read.is_open()) {
        cerr << "Errore nell'apertura del file binario per la lettura: " << file_2 << endl;
        return EXIT_FAILURE;
    }

    if (!file_text_3.is_open()) {
        cerr << "Errore nell'apertura del file di testo per la scrittura: " << file_3 << endl;
        return EXIT_FAILURE;
    }

    while(file_binary_read.read(reinterpret_cast<char*>(&l), sizeof(line))){
        file_text_3<<l.num_row<<" "<<l.num_reg<<" "<<string(l.surname)<<" "<<string(l.name)<<" "<<l.mark << endl;
    }

    file_binary_read.close();
    file_text_3.close();

    return 0;
}
