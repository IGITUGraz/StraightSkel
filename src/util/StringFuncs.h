/**
 * @file   util/StringFuncs.h
 * @author Gernot Walzl
 * @date   2013-12-16
 */

#ifndef UTIL_STRINGFUNCS_H
#define	UTIL_STRINGFUNCS_H

#include <string>
#include <vector>

namespace util {

using std::string;
using std::vector;

class StringFuncs {
public:
    virtual ~StringFuncs();
    static bool startsWith(string str, string prefix);
    static bool endsWith(string str, string suffix);
    static string trim(string str);
    static vector<string> split(string str, string delimiter, bool keep_empty);
};

}

#endif	/* UTIL_STRINGFUNCS_H */

