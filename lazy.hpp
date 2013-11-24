#ifndef LAZY_HPP_V7J57G6G
#define LAZY_HPP_V7J57G6G

#include <functional>
#include <boost/optional.hpp>

extern const bool TRACE;

template<class T>
struct lazy {
    /// CTOR: Pass builder function to constructor
    lazy(std::function<T()> fun) : fun_{fun} {}

    /// Deref: Build value or simply just return the already built value
    inline T operator*() {
        if (!val_) {
            if (TRACE) std::cout << "calculate value" << std::endl;
            val_ = fun_();
        }
        return val_.get();
    }
    
    inline T operator+ (T v) { if (TRACE) std::cout << "start cascade of calculation" << std::endl; return **this + v; }
    inline T operator- (T v) { if (TRACE) std::cout << "start cascade of calculation" << std::endl; return **this - v; }
    inline T operator* (T v) { if (TRACE) std::cout << "start cascade of calculation" << std::endl; return **this * v; }
    inline T operator/ (T v) { if (TRACE) std::cout << "start cascade of calculation" << std::endl; return **this / v; }

    /// Clear the value, force rebuilding
    inline void clear() {
        val_.reset();
    }

    std::function<T()> fun_ = nullptr;  ///< Store builder
    boost::optional<T> val_ = nullptr;  ///< Memoize value
    
};
#endif /* end of include guard: LAZY_HPP_V7J57G6G */
