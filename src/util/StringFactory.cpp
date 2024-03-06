/**
 * @file   util/StringFactory.cpp
 * @author Gernot Walzl
 * @date   2011-12-19
 */

#include "StringFactory.h"

namespace util {

const string StringFactory::DATE_FORMAT = "%Y-%m-%d_%H%M%S";

StringFactory::~StringFactory() {
    // intentionally does nothing
}

string StringFactory::fromBoolean(bool value) {
    string result;
    if (value) {
        result = "true";
    } else {
        result = "false";
    }
    return result;
}

string StringFactory::fromInteger(int value) {
    stringstream sstr;
    sstr << value;
    return sstr.str();
}

string StringFactory::fromFloat(float value) {
    stringstream sstr;
    sstr.precision(4);
    sstr << value;
    return sstr.str();
}

string StringFactory::fromFloatArr(int length, float value[]) {
    string result;
    result += "<";
    for (int i = 0; i < length; i++) {
        if (i > 0) {
            result += ", ";
        }
        result += fromFloat(value[i]);
    }
    result += ">";
    return result;
}

string StringFactory::fromDouble(double value) {
    stringstream sstr;
    sstr.precision(4);
    sstr << value;
    return sstr.str();
}

string StringFactory::fromDoubleArr(int length, double value[]) {
    string result;
    result += "<";
    for (int i = 0; i < length; i++) {
        if (i > 0) {
            result += ", ";
        }
        result += fromDouble(value[i]);
    }
    result += ">";
    return result;
}

string StringFactory::fromPointer(const void* value) {
    stringstream sstr;
    sstr << value;
    return sstr.str();
}

string StringFactory::replaceAll(string str, string search, string replace) {
    string result = str;
    size_t pos = result.find(search);
    while (pos != string::npos) {
        result.replace(pos, search.size(), replace);
        pos = result.find(search, pos+replace.size());
    }
    return result;
}

string StringFactory::now(string format) {
    boost::local_time::local_time_facet* facet =
            new boost::local_time::local_time_facet(format.c_str());
    stringstream date_stream;
    date_stream.imbue(std::locale(date_stream.getloc(), facet));
    date_stream << boost::local_time::local_microsec_clock::local_time(
            boost::local_time::time_zone_ptr());
    return date_stream.str();
//    time_t rawtime;
//    time(&rawtime);
//    struct tm * timeinfo = localtime(&rawtime);
//    char result[256];
//    strftime(result, sizeof(result), format.c_str(), timeinfo);
//    return string(result);
}

}
