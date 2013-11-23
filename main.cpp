#include <iostream>
#include <string>
#include <cassert>

#include "lazy.hpp"

bool TRACE = true;
bool PRINT = true;

std::string build_some_string() {
    return std::string{"foo"} + std::string{"bar"};
}

int main() {
    lazy<int> foo( []()->int{
        if (TRACE) std::cout << "NOW" << std::endl;
        return 2+3;
    });

    assert( *foo == 2+3 );


    lazy<int> bar( [&]{
        return *foo + 3;
    });

    assert( *bar == 2+3+3 );


    lazy<std::string> baz(build_some_string);
    
    assert( *baz == "foobar" );
    
    int i = *foo;
    assert( i == 2+3 );

    int j = *foo;
    assert( j == i );
    assert( j == 2+3 );
    assert( j == [](){ return 2+3; }() );

    if (PRINT) {
        std::cout << "HERE" << *foo << "THERE" << std::endl;
        std::cout << i+j << std::endl;
        std::cout << *bar << std::endl;
        std::cout << *baz << std::endl;
    }
    return 0;
}