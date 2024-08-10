#include "../StackHeader/Stack.h"


int main() {
    stack<int> s = {1,2,3,4,5}; 
    stack<int> s1 = {5,4,3,2,1};
    s.print();    
    std::cout << s[0] << std::endl; 
  std::cout << s.top();
    std::cout << s.empty();
    s._swap(s1);
    s.print();

}
