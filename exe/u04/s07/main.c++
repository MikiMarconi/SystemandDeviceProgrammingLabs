#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class vettore{
    private:
        vector<T> v ;
    public:
        void valpop(){
            v.pop_back();
        }

        void valpush(T val){
            v.push_back(val);
        }

        void stampa(){
            for(auto i : v){
                cout<< i<< endl;
            }
        }

};

int main(){
    vettore<int> vecval;
    vettore <string> vecstr;
    int valore;
    string parola;

    cout << "inserisci valore: ";
    cin >> valore;
    vecval.valpush(valore);

    cout << "inserisci valore: ";
    cin >> valore;
    vecval.valpush(valore);
    
    cout << "inserisci parola: ";
    cin >> parola;
    vecstr.valpush(parola);
    
    cout << "inserisci parola: ";
    cin >> parola;
    vecstr.valpush(parola);

    vecval.stampa();
    vecstr.stampa();

    vecstr.valpop();
    vecval.valpop();

    vecval.stampa();
    vecstr.stampa();
    return 0;
}