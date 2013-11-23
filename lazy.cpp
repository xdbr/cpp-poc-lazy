#include <iostream>
#include <string>
#include <functional>
#include <boost/optional.hpp>

bool TRACE = true;

template<class T>
struct lazy {
    lazy(std::function<T()> fun) : fun_{fun} {}

    T operator*() {
        if (!val_) val_ = fun_();
        return val_.get();
    }

    std::function<T()> fun_ = nullptr;
    boost::optional<T> val_ = nullptr;
};

int main() {
    lazy<int> foo( []()->int{
        if (TRACE) std::cout << "NOW" << std::endl;
        return 2+3;
    });

    lazy<int> bar( [&]{
        return *foo + 3;
    });
    
    int i = *foo;
    int j = *foo;
    std::cout << "HERE" << *foo << "THERE" << std::endl;
    std::cout << *bar << std::endl;
    return 0;
}