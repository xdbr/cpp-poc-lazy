#include <iostream>
#include <string>
#include <cassert>

#include "lazy.hpp"

extern const bool TRACE = true; // get to see when values are calculated
extern const bool PRINT = true;

std::string build_some_string() {
    return std::string{"foo"} + std::string{"bar"};
}

int main() {
    lazy<int> foo( [&]{
        return 2+3;
    });

    // will push out calculation to latest point possible
     lazy<int> bar( [&]{
        return foo * 3;
    });

    assert( *bar == (2+3)*3 );          // value will be calculated
    std::cout << *bar << std::endl;     // no need for re-calculation

    lazy<std::string> foo_string( [&]{
        return std::string{"foo"};
    });
    
    lazy<std::string> foobar_string( [&]{
        return foo_string + std::string{"bar"};
    });
    
    std::cout << *foobar_string << std::endl;

    return 0;
}