#include <iostream>
#include <deque>
#include <string>
#include <vector>


using namespace std;
template <class T>

class Stack{

    private:
    deque<T> tail;

    public:

    void push(const T &element){
        tail.push_front(element);
    }

    void pop(){
        tail.pop_front();
    }

    void visit(){
        cout<<"deque"<<endl;
        for(auto it= tail.begin(); it!= tail.end(); ++it){
            cout<<*it<<endl;
        }

    }

    void size(){
        cout<<"deque"<<endl;
        cout<<tail.size()<<endl;
    }

    void empty(){
        cout<<"La deque e' vuota(1) o non vuota(0): "<<tail.empty()<<endl;
    }

};

template <class T>
class Stackvector{

    private:
    vector<T> vec;

    public:

    void push(const T &element){
        vec.push_back(element);
    }

    void pop(){
        vec.pop_back();
    }

    void visit(){
        cout<<"vettore"<<endl;
        for(auto it= vec.begin(); it!= vec.end(); ++it){
            cout<<*it<<endl;
        }

    }

    void size(){
        cout<<"vettore"<<endl;
        cout<<vec.size()<<endl;
    }

    void empty(){
        cout<<"La deque e' vuota(1) o non vuota(0): "<<vec.empty()<<endl;
    }

};


int main(int argc, char **argv){

    Stack<int> s;
    Stackvector<int> v;
    bool flag=true;
    int choice;
    int val;

    while (flag)
    {
        cin>>choice;
        switch (choice)
        {
        case 0:
            cout<<"Inserisci un valore: ";
            cin>>val;
            s.push(val);
            v.push(val);
            break;
        case 1:
            s.pop();
            v.pop();
            break;
        case 2:
            s.visit();
            v.visit();
            break;
        case 3:
            s.size();
            v.size();
            break;
        case 4:
            s.empty();
            v.empty();
            break;
        case 5: 
            flag=false;
            break;
        default:
            
            break;
        }
    }
    return 0;

}