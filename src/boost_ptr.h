/**
 * @file   boost_ptr.h
 * @author Gernot Walzl
 * @date   2012-10-17
 */

#ifndef BOOST_PTR_H
#define	BOOST_PTR_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "config.h"
#ifdef DEBUG
    #include "util/SharedPtr.h"
    #define SHARED_PTR util::SharedPtr
#else
    #define SHARED_PTR boost::shared_ptr
#endif

#include "util/WeakPtr.h"
#define WEAK_PTR util::WeakPtr

#endif	/* BOOST_PTR_H */

