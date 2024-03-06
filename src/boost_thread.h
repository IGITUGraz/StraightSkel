/**
 * @file   boost_thread.h
 * @author Gernot Walzl
 * @date   2011-11-21
 */

#ifndef BOOST_THREAD_H
#define	BOOST_THREAD_H

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "boost_ptr.h"

typedef SHARED_PTR<boost::thread> ThreadSPtr;


#include <boost/thread/recursive_mutex.hpp>

typedef boost::recursive_mutex RecursiveMutex;
typedef boost::recursive_mutex::scoped_lock Lock;

#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
    #include <boost/thread/shared_mutex.hpp>
    #include <boost/thread/locks.hpp>

    typedef boost::shared_mutex SharedMutex;
    typedef boost::shared_lock<boost::shared_mutex> ReadLock;
    typedef boost::unique_lock<boost::shared_mutex> WriteLock;

    inline void boost_thread_sleep(unsigned int sleep_ms) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(sleep_ms));
    }
#else
    typedef boost::recursive_mutex SharedMutex;
    typedef boost::recursive_mutex::scoped_lock ReadLock;
    typedef boost::recursive_mutex::scoped_lock WriteLock;

    inline void boost_thread_sleep(unsigned int sleep_ms) {
        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.nsec += (sleep_ms * 1000000);
        boost::thread::sleep(xt);
    }
#endif

#endif	/* BOOST_THREAD_H */
