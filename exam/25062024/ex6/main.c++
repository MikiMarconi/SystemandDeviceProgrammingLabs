#include <future>
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>


void merge(std::vector<float>& vect, int left, int mid, int right) {
    std::vector<float> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (vect[i] <= vect[j]) temp.push_back(vect[i++]);
        else temp.push_back(vect[j++]);
    }
    while (i <= mid) temp.push_back(vect[i++]);
    while (j <= right) temp.push_back(vect[j++]);

    for (int k = 0; k < temp.size(); ++k)
        vect[left + k] = temp[k];
}

void mergesort(std::vector<float>& vect, int left, int right){

    if(left>=right){
        return;
    }
    int mid = left + (right-left) / 2;
    auto fut1 = std::async(std::launch::async, mergesort, std::ref(vect), left, mid);
    auto fut2 = std::async(std::launch::async, mergesort, std::ref(vect), mid+1, right);  
    fut1.get();  
    fut2.get();
    merge(vect, left, mid, right);
    return;
}


int main(){
    std::vector<float> vect;
    auto fut = std::async(std::launch::async, mergesort, std::ref(vect), 0, vect.size()-1);
    int i;
    for(i=0; i<4;i++){
        vect.push_back(rand()%100);
    }
    std::cout << "Before:\n";
    for (auto val : vect) std::cout << val << " ";
    std::cout << "\n";
    fut.get();
    std::cout << "After:\n";
    for (auto val : vect) std::cout << val << " ";
    std::cout << "\n";

    return 0;

}