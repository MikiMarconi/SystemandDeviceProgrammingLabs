#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


double temperature = 18.5;
double targettemp=18.0;
bool heatingsystemactive=false;
bool stop= false;
std::mutex mtx, mtx_out;


void adminfun(){
    while (!stop)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        {
            std::lock_guard<std::mutex> lock(mtx);
            {
                std::lock_guard<std::mutex> lock(mtx_out);
                std::cout<<"Temperatura attuale: "<<temperature<<" heating system: "<<heatingsystemactive<<std::endl;
            }

            if(heatingsystemactive){

                if(temperature>targettemp+0.2){

                    heatingsystemactive= false;
                }
            }else{
                
                if(temperature<=targettemp+0.2){

                    heatingsystemactive= true;
                }

            }

        }
        
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (targettemp==-1)
            {
                break;
            }
        }


    }
}

void curtempfun(){
    while (!stop)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (heatingsystemactive)
            {
                
                temperature+=0.3;
                {
                    std::lock_guard<std::mutex> lock(mtx_out);
                    std::cout<<"Temperatura cambiata: "<<temperature<<" heating system: "<<heatingsystemactive<<std::endl;
                }
            }else{
                temperature-=0.3;
                {
                    std::lock_guard<std::mutex> lock(mtx_out);
                    std::cout<<"Temperatura cambiata: "<<temperature<<" heating system: "<<heatingsystemactive<<std::endl;
                }
            }
        }


        {
            std::lock_guard<std::mutex> lock(mtx);
            if (targettemp==-1)
            {
                break;
            }
        }

    }
    

}

void tartempfun(){
    while (!stop)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        {
            std::lock_guard<std::mutex> lock(mtx);

            {
                std::lock_guard<std::mutex> lock(mtx_out);
                std::cout<<"Inserisci la temperatura desiderata: ";
                std::cin>>targettemp;
            }
            if (targettemp==-1)
            {
                break;
            }
            
        }

    }    
}

int main(){

    std::thread admin(adminfun);
    std::thread targetTemp(tartempfun);
    std::thread currentTemp(curtempfun);

    admin.join();
    targetTemp.join();
    currentTemp.join();


}



