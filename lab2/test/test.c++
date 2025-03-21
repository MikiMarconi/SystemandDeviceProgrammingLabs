#include <iostream>
#include <fstream>

using namespace std;

struct Record{
    int row;
    long reg;
    char surname[31];
    char name[31];
    int mark;
};

int main(int argc, char **argv){

    if(argc!=4){
        cerr<< "Argument error" << endl;
        return EXIT_FAILURE;
    }

    ifstream filein(argv[1]);
    ofstream binaryfile(argv[2], ios::binary);

    if(!filein.is_open()){
        cerr<< "File error"<< argv[1] << endl;
        return EXIT_FAILURE;
    }
    if(!binaryfile.is_open()){
        cerr<< "File error" << argv[2] << endl;
        return EXIT_FAILURE;
    }

    /*
    record → È un oggetto della struttura Record contenente i dati.

    reinterpret_cast<char*> → Converte l'indirizzo di record in un puntatore a carattere (char*), necessario perché il metodo .write() lavora con buffer di byte.

    sizeof(Record) → Indica la dimensione in byte della struttura Record, cioè quanti byte devono essere scritti nel file.
    */
    Record r;

    while(filein >>  r.row >> r.reg >> r.surname >> r.name >> r.mark){
        binaryfile.write(reinterpret_cast<char*>(&r), sizeof(Record));
    }

    filein.close();
    binaryfile.close();

    ifstream binaryin(argv[2], ios::binary);
    ofstream fileout(argv[3], ios::out);

    if(!binaryin.is_open()){
        cerr<< "File error" << argv[2] << endl;
        return EXIT_FAILURE;
    }

    if(!fileout.is_open()){
        cerr<< "File error" << argv[3] << endl;
        return EXIT_FAILURE;
    }

    while (binaryin.read(reinterpret_cast<char*>(&r), sizeof(Record))) {
        fileout << r.row << " " << r.reg << " " << r.surname << " " << r.name << " " << r.mark << endl;
    }

    binaryin.close();
    fileout.close();
    return EXIT_SUCCESS;
}