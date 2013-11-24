#include <iostream>
#include <string>
#include <cassert>

#include "lazy.hpp"

int main() {

    //_____________ E X A M P L E  1 ______________________________________//

    lazy<std::string> foo_string( []{
        return std::string{"foo"};
    });

    lazy<std::string> bar_string( []{
        return std::string{"bar"};
    });

    lazy<std::string> foobarbaz_string( [&]{
        return foo_string + bar_string + std::string{"baz"};
    });

    // only now kick off the cascade
    std::cout << *foobarbaz_string << std::endl;

    assert( *foobarbaz_string == "foobarbaz" );  // no need for re-calculation


    //_____________ E X A M P L E  2 ______________________________________//

    lazy<int> one( []{
        return 1; // in real life, this would be complex & long-running
    });

    // push out calculation to latest point possible
    lazy<int> two( [&]{
        return one + 1;
    });

    // will push out calculation to even more 'latest point possible'
    lazy<int> four( [&]{
        return one + two + 1;
    });

    // now start calculation (possibly a cascade of calculations)
    std::cout << *four << std::endl;

    assert( *four == 4 );          // no need for re-calculation

    //_____________ E X A M P L E  3 ______________________________________//

    four.clear();           // force re-calculation

    assert( *four == 4 );   // will need re-calculation

    return 0;
}