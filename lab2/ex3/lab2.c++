#include <iostream>
#include <vector>

using namespace std;

class MyStack{

    private: 
        vector<int> stack;
    
    public:
        void push(int value){
            stack.push_back(value);
        }

        void pop(){
            stack.pop_back();
        }

        void visit(){
            for(int i=0; i<stack.size(); i++){
                cout<< stack[i]<<endl;
            }
        }

        void getSize(){
            cout<<""<< stack.size()<<endl;
        }

        void empty(){
            if(stack.empty()){
                cout<<"true"<<endl;
            }
        }

};

int main(){
    MyStack s;
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
            break;
        case 1:
            s.pop();
            break;
        case 2:
            s.visit();
            break;
        case 3:
            s.getSize();
            break;
        case 4:
            s.empty();
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