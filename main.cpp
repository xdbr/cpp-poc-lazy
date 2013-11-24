#include <iostream>
#include <string>
#include <cassert>

#include "lazy.hpp"

extern const bool TRACE = true; // get to see when values are calculated
extern const bool PRINT = true;

int main() {

#ifndef DODEBUG
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


#else /*DODEBUG*/

    if (TRACE) std::cout << "\n"
    "//_____________ E X A M P L E  1 ______________________________________//"
    << std::endl;

    lazy<std::string> foo_string( "foo_string", []{
        return std::string{"foo"};
    });

    lazy<std::string> bar_string( "bar_string", []{
        return std::string{"bar"};
    });

    lazy<std::string> foobarbaz_string( "foobarbaz_string", [&]{
        return foo_string + bar_string + std::string{"baz"};
    });

    // only now kick off the cascade
    std::cout << *foobarbaz_string << std::endl;
    std::cout << std::endl << "CLEAR" << std::endl << std::endl;
    foobarbaz_string.clear();
    std::cout << *foobarbaz_string << std::endl; // no need for re-calculation

    // #if 0
    // assert( *foobarbaz_string == "foobarbaz" );

    if (TRACE) std::cout << "\n"
    "//_____________ E X A M P L E  2 ______________________________________//"
    << std::endl;
    lazy<int> one( "one", []{
        return 1; // in real life, this would be complex & long-running
    });

    // push out calculation to latest point possible
    lazy<int> two( "two", [&]{
        return one + 1;
    });

    // will push out calculation to even more 'latest point possible'
    lazy<int> four( "four", [&]{
        return one + two + 1;
    });

    // now start calculation (possibly a cascade of calculations)
    std::cout << *four << std::endl;

    assert( *four == 4 );          // no need for re-calculation

    if (TRACE) std::cout << "\n"
    "//_____________ E X A M P L E  3 ______________________________________//"
    << std::endl;

    four.clear();

    std::cout << *four << std::endl;
    // #endif /*0*/
#endif /*DODEBUG*/

    return 0;
}