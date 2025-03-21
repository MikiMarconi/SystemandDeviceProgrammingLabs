#include <iostream>
#include <algorithm>
#include <cstdlib>  // Per usare malloc e free

// Funzione per allocare i numeri
void allocateNum(float* array, int n) {
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
}

// Funzione per ordinare l'array
void sort(float* array, int n) {
    std::sort(array, array + n);
}

// Funzione per visualizzare l'array
void displayVett(float* array, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "valore: " << array[i] << std::endl;
    }
}

int main() {
    int n;
    std::cin >> n;

    // Allocazione dinamica della memoria per l'array di float
    float* array = (float*) malloc(n * sizeof(float));  // Malloc per allocare memoria per float

    // Verifica se malloc ha avuto successo
    if (array == nullptr) {
        std::cerr << "Errore di allocazione memoria!" << std::endl;
        return 1;  // Esci con errore
    }

    // Chiamata alle funzioni
    allocateNum(array, n);
    sort(array, n);
    displayVett(array, n);

    // Libera la memoria allocata
    free(array);

    system("pause");

    return 0;
}
