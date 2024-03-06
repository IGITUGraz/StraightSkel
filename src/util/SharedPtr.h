/**
 * @file   util/SharedPtr.h
 * @author Gernot Walzl
 * @date   2012-02-28
 */

#ifndef UTIL_SHAREDPTR_H
#define	UTIL_SHAREDPTR_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <iostream>
#include "util/StackTrace.h"

namespace util {

template<class T> class SharedPtr : public boost::shared_ptr<T> {
public:
    SharedPtr() : boost::shared_ptr<T>() {}
    explicit SharedPtr(T* p) : boost::shared_ptr<T>(p) {}
    template<class Y> SharedPtr(const SharedPtr<Y>& r) : boost::shared_ptr<T>(r) {}
    SharedPtr(const boost::shared_ptr<T>& r) : boost::shared_ptr<T>(r) {}
    SharedPtr(const boost::weak_ptr<T>& r) : boost::shared_ptr<T>(r) {}

    T& operator*() const {
        if (this->use_count() == 0) {
            std::cerr << "Error: Shared Pointer is invalid." << std::endl;
            StackTrace::print(std::cerr);
        }
        return boost::shared_ptr<T>::operator*();
    }
    T* operator->() const {
        if (this->use_count() == 0) {
            std::cerr << "Error: Shared Pointer is invalid." << std::endl;
            StackTrace::print(std::cerr);
        }
        return boost::shared_ptr<T>::operator->();
    }
};

}

#endif	/* UTIL_SHAREDPTR_H */

