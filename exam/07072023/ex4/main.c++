#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>

struct hashMapEntry{
    std::string name; 
    std::string surname;
    std::set<int> marks;
};


std::map<int, hashMapEntry>* functionhash(std::string filename){

    std::ifstream text_file(filename);
    if(!text_file.is_open()){
        std::cerr<<"Error";
    }
    auto* map = new std::map<int, hashMapEntry>();

    int number;
    int nmarks;
    while(text_file>>number){
        hashMapEntry entry;
        text_file>>entry.surname>>entry.name;
        text_file>>nmarks;
        int i;
        for(i=0; i<nmarks; i++){
            int mark;
            text_file>>mark;
            entry.marks.emplace(mark);
        }

        (*map)[number]= entry;
    }

    text_file.close();
    return map;
}


int main(int argc, char** argv){

    if(argc!=2){
        std::cerr<<"Error";
    }
    std::string filename = argv[1];
    std::map<int, hashMapEntry>* studentMap = functionhash(filename);


    for (const auto& [number, entry] : *studentMap) {
        std::cout << "Matricola: " << number << "\n"
                    << "Nome: " << entry.name << ", Cognome: " << entry.surname << "\n"
                    << "Voti: ";
        for (int mark : entry.marks) {
            std::cout << mark << " ";
        }
        std::cout << "\n\n";
    }

    delete studentMap;  
    return 0;

}