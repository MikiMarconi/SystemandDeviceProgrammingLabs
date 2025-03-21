#include <iostream>
#include <string>  
#include <fstream>

using namespace std;

struct line{
    int num_row;
    long num_reg;
    char surname[31];
    char name[31];
    int mark;
};


int main() {
    char file_1[50];
    char file_2[50];
    char file_3[50];
    char selection;
    int n;
    bool loop=true;
    char choice;

    cin >> file_1;

    fstream filein(file_1, ios::in | ios::out | ios::binary);


    if (!filein.is_open()) {
        cerr << "Errore nell'apertura del file di testo: " << file_1 << endl;
        return EXIT_FAILURE;
    }

    line l;



        while(loop){
            cout << "Seleziona operazione" << endl;
            cin >> selection ;
            switch (selection)
            {
            case 'R':
                cin >> n;
                filein.seekg((n-1)*sizeof(line), ios::beg);
                filein.read(reinterpret_cast<char*>(&l), sizeof(line));
                cout << l.num_row << " " << l.num_reg << " " << l.surname << " " << l.name << " " << l.mark << endl;
                break;
            case 'W':
                cin >> n;
                cout << "Inserisci nuovo record" << endl;
                cin >> l.num_row >> l.num_reg >> l.surname >> l.name >>l.mark;
                filein.seekg((n-1)*sizeof(line), ios::beg);
                filein.write(reinterpret_cast<char*>(&l), sizeof(line));
                break;
            case 'E':
                loop=false;
                break;
            default:
                break;
            }
        }
    filein.close();
    return 0;    

}
