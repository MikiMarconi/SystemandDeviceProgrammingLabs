#include <iostream>
#include <sys/shm.h>
#include <random>
#include <unistd.h>
#include <vector>

#define SHM_SIZE 1024

float randomfloatval(){
    static std::random_device = rd;
    static std::mt19937 gen(rd());
    return std::uniform_real_distribution<float>(-100, 100) (gen);
}

int randomintval(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int>(0, 10) (gen);

}


int main(){
    pid_t pid = fork();
    key_t key = ftok("shmfile", 65);
    int fd[2];
    pipe(fd);
    int shmid= shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

    if(shmid==-1){
        std::cerr<<"error";
    }

    if(pid==0){
        while(true){
            char* data = (char *)shmat(shmid, NULL, 0);
            int iteration= randomintval();
            int i;
            for(i=0; i<iteration; i++){
                strcpy(data, (std::string)randomfloatval());
            }

            char token;
            token= 'A';
            write(fd[1], &token, 1);
            read(fd[0], &token, 1);
        }

    }else{
        while(true){
            char* data= (char *)shmat(shmid, NULL, 0);
            char token;
            read(fd[0], &token, 1);
            int i;
            std::vector<float> vectorfloat;
            strcpy(vectorfloat, data);
            for(auto &v : vectorfloat){
                std::cout<<"float: "<< v <<" ";
            }        

            write(fd[1], &token, 1);

        }
    }

}

