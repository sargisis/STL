#include "../forward_list/forward_list.h"
#include <iostream>

int main() 
{
    g3::forward_list<int> b = {1,2,3,4,5};
   
    g3::forward_list<int> b1 = std::move(b);
    for (const auto& it : b1) 
    {
        std::cout << it; 
    }
}