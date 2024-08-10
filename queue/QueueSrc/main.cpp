#include "../QueueHeader/Queue.h"


int main(){
    queue<int> s = {1,2,3,4,5 , 6, 7 , 8 , 9 , 10};
    s.print();
    std::cout << s[0] << std::endl; 
    std::cout << s[1] << std::endl; 
    std::cout << s.front() << std::endl; 
    
}
