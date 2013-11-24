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

#else /*DODEBUG*/

template<class T>
struct lazy {
    lazy(std::string id, std::function<T()> fun) : fun_{fun}, id_{id} {}
    
    // might be useful?
    // inline operator T () {
    //     return **this;
    // }
    inline T operator*() const {
        if (val_) if (TRACE) std::cout << "value for object with id_ = " << id_ << " is calculated already" << std::endl;
        if (!val_) {
            if (TRACE) std::cout << "lazy object with id = ("<<id_<<")" " needs calculation " << std::endl;
            val_ = fun_();
        }
        if (TRACE) std::cout << "returning value for lazy object with id_ = " << id_ << ": " << val_.get() << std::endl;
        return val_.get();
    }

    // lazy OP value -> (calculated) value
    inline T operator+ (T v) { if (TRACE) std::cout << std::string(++depth, ' ') << "lazy OP value -> calculate value for object with id = " << id_ << " and RHS value = " << v << std::endl; if(depth > 0)--depth; return (**this) + (v); }
    inline T operator- (T v) { if (TRACE) std::cout << std::string(++depth, ' ') << "lazy OP value -> calculate value for object with id = " << id_ << " and RHS value = " << v << std::endl; if(depth > 0)--depth; return (**this) - (v); }
    inline T operator* (T v) { if (TRACE) std::cout << std::string(++depth, ' ') << "lazy OP value -> calculate value for object with id = " << id_ << " and RHS value = " << v << std::endl; if(depth > 0)--depth; return (**this) * (v); }
    inline T operator/ (T v) { if (TRACE) std::cout << std::string(++depth, ' ') << "lazy OP value -> calculate value for object with id = " << id_ << " and RHS value = " << v << std::endl; if(depth > 0)--depth; return (**this) / (v); }

    // lazy OP lazy -> (new) lazy
    inline lazy<T> operator+ (lazy<T> v) { if (TRACE) { std::cout << std::string(++depth, ' ') << "lazy OP lazy -> lazy" << std::endl; } return lazy<T>( v.id_+"-a", [&]{ return (**this) + (*v); }); }
    inline lazy<T> operator- (lazy<T> v) { if (TRACE) { std::cout << std::string(++depth, ' ') << "lazy OP lazy -> lazy" << std::endl; } return lazy<T>( v.id_+"-a", [&]{ return (**this) - (*v); }); }
    inline lazy<T> operator* (lazy<T> v) { if (TRACE) { std::cout << std::string(++depth, ' ') << "lazy OP lazy -> lazy" << std::endl; } return lazy<T>( v.id_+"-a", [&]{ return (**this) * (*v); }); }
    inline lazy<T> operator/ (lazy<T> v) { if (TRACE) { std::cout << std::string(++depth, ' ') << "lazy OP lazy -> lazy" << std::endl; } return lazy<T>( v.id_+"-a", [&]{ return (**this) / (*v); }); }

    /// Clear the value, force rebuilding
    inline void clear() {
        val_.reset();
    }

    std::function<T()> fun_ = nullptr;  ///< Store builder
    mutable boost::optional<T> val_ = nullptr;  ///< Memoize value
    
    int depth{0};
    std::string id_;
};

#endif /*DODEBUG*/

#endif /* end of include guard: LAZY_HPP_V7J57G6G */
