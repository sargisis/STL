#include "Vector.h"


int main() {
    g3::vector<int> a = {1,2,3,4,5,6};
     for(const auto& elem : a) {
        std::cout << elem;
     }
     std::cout << std::endl; 
    std::cout << "Insert vector " << std::endl;  
     a.insert(a.begin() + 2 , {10,20,30,40,50}); 
     for(const auto& elem : a) {
        std::cout << elem << " ";
     }
    std::cout << "after insert vector " << std::endl;

    std::cout << "Erase this vector full"  << std::endl; 
    a.erase(a.begin() , a.end());
    for(const auto& elem : a) {
        std::cout << elem;
     }

    std::cout << "New vector " << std::endl; 
    g3::vector<int> a1 = {1,2,3,4,5,6};
    for(const auto& elem : a1) {
        std::cout << elem << " ";
     }
    std::cout << std::endl; 

    std::cout << "Add new elements " << std::endl; 
    a1.insert(a1.begin(), 5,33);
    for(const auto& elem : a1) {
        std::cout << elem <<  " ";
     }
    std::cout << std::endl; 
    std::cout << "Ereased this vector " << std::endl; 
    a1.erase(a1.begin(), a1.end());
    for(const auto& elem : a) {
        std::cout << elem << " ";
     }
}