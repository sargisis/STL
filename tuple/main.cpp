#include <iostream>
#include "tuple.h"

int main() {
    g3::tuple<int, double> f(1, 5.5);
    g3::tuple<int , double> f1(5,55.5);
    
    auto x = f.get_rest().get_val();

    std::cout << x;

    
}
