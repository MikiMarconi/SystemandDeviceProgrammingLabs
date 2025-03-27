#include <iostream>
#include <string>  
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct student{
    int id;
    string name;
    int grade;
};



int main(int argc, char **argv){

    student s;
    bool choice=true;
    bool wh=true;
    string scelta;
    list<student> listastudenti;
    int criteria;
    while(choice){

        cout<<"Vuoi inserire uno studente?(si/no)"<<endl;
        cin>>scelta;
        if(scelta=="si"){
            cout<<"Inserisci uno studente, ID: ";
            cin>>s.id;
            cout<<"Nome: ";
            cin>>s.name;
            cout<<"Grade: ";
            cin>>s.grade;
            listastudenti.push_back(s);
        }else{
            choice=false;
        }
    }


    while(wh){
        cout<<"Scegli il criterio di sort:"<<endl;
        cout<<"1)ID"<<endl;
        cout<<"2)Name"<<endl;
        cout<<"3)Grade"<<endl;
        cout<<"4)Exit"<<endl;
        cin>>criteria;
        switch (criteria)
        {
        case 1:
            listastudenti.sort([](const student& a, const student& b){
                return a.id<b.id;
            });

            for (const auto& s: listastudenti){
                cout<< s.id<<" "<<s.name<<" "<<s.grade<<endl;
            }
            break;
        case 2:
            listastudenti.sort([](const student& a, const student& b){
                return a.name<b.name;
            });

            for (const auto& s: listastudenti){
                cout<< s.id<<" "<<s.name<<" "<<s.grade<<endl;
            }
            break;
        case 3:
            listastudenti.sort([](const student& a, const student& b){
                return a.grade<b.grade;
            });

            for (const auto& s: listastudenti){
                cout<< s.id<<" "<<s.name<<" "<<s.grade<<endl;
            }
            break;
        case 4:
            wh= false;
            break;
        default:
            break;
        }
    }

    return 0;

}