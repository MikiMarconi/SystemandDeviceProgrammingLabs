#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " input.bin output.txt" << endl;
        return EXIT_FAILURE;
    }

    ifstream in(argv[1], ios::binary);
    if (!in.is_open()) {
        cerr << "Errore apertura file binario: " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    int total;
    in.read(reinterpret_cast<char*>(&total), sizeof(int));
    if (in.fail()) {
        cerr << "Errore nella lettura del numero totale di valori" << endl;
        return EXIT_FAILURE;
    }

    vector<int> values(total);
    in.read(reinterpret_cast<char*>(values.data()), total * sizeof(int));
    if (in.fail()) {
        cerr << "Errore nella lettura dei valori" << endl;
        return EXIT_FAILURE;
    }
    in.close();

    ofstream out(argv[2]);
    if (!out.is_open()) {
        cerr << "Errore apertura file di output: " << argv[2] << endl;
        return EXIT_FAILURE;
    }

    out << total << " ";
    for (int val : values) {
        out << val << " ";
    }
    out << endl;

    cout << "Conversione completata." << endl;
    return 0;
}
