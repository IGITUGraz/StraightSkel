/**
 * @file   util/StringFactory.h
 * @author Gernot Walzl
 * @date   2011-12-19
 */

#ifndef UTIL_STRINGFACTORY_H
#define	UTIL_STRINGFACTORY_H

#include <string>
#include <sstream>
#include <iomanip>
#include <boost/date_time/local_time/local_time.hpp>

namespace util {

using std::string;
using std::stringstream;

class StringFactory {
public:
    virtual ~StringFactory();
    static string fromBoolean(bool value);
    static string fromInteger(int value);
    static string fromFloat(float value);
    static string fromFloatArr(int length, float value[]);
    static string fromDouble(double value);
    static string fromDoubleArr(int length, double value[]);
    static string fromPointer(const void* value);
    static string replaceAll(string str, string search, string replace);

    static const string DATE_FORMAT;

    /**
     * @param format  %Y-%m-%d_%H%M%S
     */
    static string now(string format);
};

}

#endif	/* UTIL_STRINGFACTORY_H */

