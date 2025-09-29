#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <thread>


int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr<< "Usage: %s <input_file> <output_file>\n";
        return EXIT_FAILURE;
    }

   int fdin; 
   size_t cpys;
   struct stat st;
   off_t fsz=0;

   fdin = open(argv[1], )

   


    return 0;

}