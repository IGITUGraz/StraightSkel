/**
 * @file   util/WeakPtr.h
 * @author Gernot Walzl
 * @date   2012-03-29
 */

#ifndef UTIL_WEAKPTR_H
#define	UTIL_WEAKPTR_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace util {

/**
 * Adds operator== to boost::weak_ptr.
 * This allows to use the WeakPtr in the STL (e.g. list).
 */
template<class T> class WeakPtr : public boost::weak_ptr<T>  {
public:
    WeakPtr() : boost::weak_ptr<T>() {}
    template<class Y> WeakPtr(const WeakPtr<Y>& r) : boost::weak_ptr<T>(r) {}
    WeakPtr(const boost::weak_ptr<T>& r) : boost::weak_ptr<T>(r) {}
    WeakPtr(const boost::shared_ptr<T>& r) : boost::weak_ptr<T>(r) {}

    bool operator==(const boost::weak_ptr<T>& other) const {
        bool result = (this->expired() && other.expired());
        if (!this->expired() && !other.expired()) {
            result = (this->lock() == other.lock());
        }
        return result;
    }
    bool operator!=(const boost::weak_ptr<T>& other) const {
        return !operator==(other);
    }
};

}

#endif	/* UTIL_WEAKPTR_H */

