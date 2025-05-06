#include <iostream>
#include <fstream>

using namespace std;

void writeBinaryFile(const string& filename, const int* data, int count) {
    ofstream out(filename, ios::binary);
    if (!out.is_open()) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        return;
    }
    out.write(reinterpret_cast<const char*>(&count), sizeof(int));
    out.write(reinterpret_cast<const char*>(data), count * sizeof(int));
    out.close();
}

int main() {
    int file1[] = {23, 45, 67, 9, 23};
    int file2[] = {90, 65, 34, 24, 12, 0, 89, 29, 54, 12, 78, 3};
    int file3[] = {9, 5, 1};

    writeBinaryFile("file1.bin", file1, 5);
    writeBinaryFile("file2.bin", file2, 12);
    writeBinaryFile("file3.bin", file3, 3);

    cout << "File binari creati correttamente." << endl;
    return 0;
}
