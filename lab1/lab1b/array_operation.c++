#include "array_operation.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>  // Per malloc e free

void allocateNum(float *array, int n) {
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
}

void sort(float *array, int n) {
    std::sort(array, array + n);  // Usa il puntatore per ordinare l'array
}

void displayVett(float *array, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "valore: " << array[i] << std::endl;
    }
}
