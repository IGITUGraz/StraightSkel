/**
 * @file   util/StackTrace.h
 * @author Gernot Walzl
 * @date   2012-02-28
 */

#ifndef UTIL_STACKTRACE_H
#define	UTIL_STACKTRACE_H

#include <cstdlib>
#include <iostream>
#ifdef __linux__
#include <execinfo.h>
#include <cxxabi.h>
#endif

namespace util {

using std::string;
using std::ostream;

class StackTrace {
public:
    virtual ~StackTrace();
    static string demangle(string symbol_mangled);
    static void print(ostream& os);
};

}

#endif	/* UTIL_STACKTRACE_H */

