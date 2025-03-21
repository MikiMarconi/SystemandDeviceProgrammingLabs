#include <iostream>
#include "array_operation.h"
#include <cstdlib>  // Per malloc e free

int main() {
    int n;
    std::cin >> n;  // Leggi la dimensione dell'array

    // Allocazione dinamica della memoria usando malloc
    float *array = (float *) malloc(n * sizeof(float));
    if (array == nullptr) {
        std::cerr << "Errore nell'allocazione della memoria!" << std::endl;
        return 1;  // Esci con codice di errore
    }

    allocateNum(array, n);  // Assegna i valori all'array
    sort(array, n);  // Ordina l'array
    displayVett(array, n);  // Mostra i valori dell'array

    free(array);  // Libera la memoria allocata
    system("pause");

    return 0;
}
