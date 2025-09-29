#include <iostream>

template<typename T>
T findMax(T a, T b){

    if(a>b){
        return a;
    }else{
        return b;
    }
}

template<typename K, typename V>
class KeyValuePair{

    private:
    K key;
    V value;

    public:
    KeyValuePair(K chosenkey, V chosenvalue){
        key = chosenkey;
        value = chosenvalue;
    }

    K getKey(){
        return key;
    }

    V getValue(){
        return value;
    }
};


int main(){
    std::cout<<findMax(1, 2)<<std::endl;
    std::cout<<findMax('a', 'b')<<std::endl;

    KeyValuePair<std::string, int> customclass("aaa", 20);
    std::cout<<customclass.getKey()<<" "<<customclass.getValue()<<std::endl;

}