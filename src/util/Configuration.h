/**
 * @file   util/Configuration.h
 * @author Gernot Walzl
 * @date   2012-10-30
 */

#ifndef UTIL_CONFIGURATION_H
#define	UTIL_CONFIGURATION_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include "debug.h"
#include "util/ptrs.h"
#include "util/StringFuncs.h"

namespace util {

using std::string;

class Configuration {
public:
    virtual ~Configuration();
    static ConfigurationSPtr getInstance();

    string findDefaultFilename();

    void parse(std::istream& input);
    bool load(const string& filename);
    bool isLoaded() const;

    bool contains(const string& section, const string& key);

    string getString(const string& section, const string& key);
    int getInt(const string& section, const string& key);
    double getDouble(const string& section, const string& key);
    bool getBool(const string& section, const string& key);

protected:
    Configuration();
    static ConfigurationSPtr instance_;

    std::map<string, string> properties_;
};

}

#endif	/* UTIL_CONFIGURATION_H */

