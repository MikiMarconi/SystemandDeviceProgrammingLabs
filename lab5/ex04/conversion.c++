#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // Aggiungi questa libreria per strncpy

struct Persona {
    int id;
    int stipendio;
    char cognome[20];
    char nome[20];
    int eta;
};

void convertTxtToBinary(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream txtFile(inputFile);
    std::ofstream binFile(outputFile, std::ios::binary);

    if (!txtFile.is_open() || !binFile.is_open()) {
        std::cerr << "Errore nell'apertura dei file." << std::endl;
        return;
    }

    Persona persona;
    std::string cognome, nome;

    while (txtFile >> persona.id >> persona.stipendio >> cognome >> nome >> persona.eta) {
        // Copia i dati nei buffer a lunghezza fissa
        strncpy(persona.cognome, cognome.c_str(), sizeof(persona.cognome) - 1);
        persona.cognome[sizeof(persona.cognome) - 1] = '\0'; // Assicurarsi che sia terminato con '\0'

        strncpy(persona.nome, nome.c_str(), sizeof(persona.nome) - 1);
        persona.nome[sizeof(persona.nome) - 1] = '\0'; // Assicurarsi che sia terminato con '\0'

        // Scrive la struttura nel file binario
        binFile.write(reinterpret_cast<char*>(&persona), sizeof(Persona));
    }

    txtFile.close();
    binFile.close();
}

int main() {
    std::string inputFile = "file.txt";
    std::string outputFile = "file.bin";

    convertTxtToBinary(inputFile, outputFile);

    std::cout << "Conversione completata!" << std::endl;
    return 0;
}