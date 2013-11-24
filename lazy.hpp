#ifndef LAZY_HPP_V7J57G6G
#define LAZY_HPP_V7J57G6G

#include <functional>
#include <boost/optional.hpp>

extern const bool TRACE;

#ifndef DODEBUG
template<class T>
struct lazy {
    lazy(std::function<T()> fun) : fun_{fun} {}

    inline T operator*() const {
        if(!val_) val_ = fun_();
        return val_.get();
    }

    // lazy OP value -> (calculated) value
    inline T operator+ (T v) { return (**this) + (v); }
    inline T operator- (T v) { return (**this) - (v); }
    inline T operator* (T v) { return (**this) * (v); }
    inline T operator/ (T v) { return (**this) / (v); }

    // lazy OP lazy -> (new) lazy
    inline lazy<T> operator+ (lazy<T> v) { return lazy<T>( [&]{ return (**this) + (*v); }); }
    inline lazy<T> operator- (lazy<T> v) { return lazy<T>( [&]{ return (**this) - (*v); }); }
    inline lazy<T> operator* (lazy<T> v) { return lazy<T>( [&]{ return (**this) * (*v); }); }
    inline lazy<T> operator/ (lazy<T> v) { return lazy<T>( [&]{ return (**this) / (*v); }); }

    /// Clear the value, force rebuilding
    inline void clear() {
        val_.reset();
    }

    const   std::function<T()> fun_ = nullptr;  ///< Store builder
    mutable boost::optional<T> val_ = nullptr;  ///< Memoize value
};

#endif /* end of include guard: LAZY_HPP_V7J57G6G */
