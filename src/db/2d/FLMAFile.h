/**
 * @file   db/2d/FLMAFile.h
 * @author Gernot Walzl
 * @date   2013-12-16
 */

#ifndef DB_2D_FLMAFILE_H
#define	DB_2D_FLMAFILE_H

#include <string>
#include <fstream>
#include <vector>
#include "util/StringFuncs.h"
#include "util/Configuration.h"
#include "db/2d/AbstractFile.h"

namespace db { namespace _2d {

using std::string;
using std::ifstream;
using std::vector;
using namespace data::_2d;

/**
 * AVL flma file format
 */
class FLMAFile : public AbstractFile {
public:
    virtual ~FLMAFile();
    static PolygonSPtr load(string filename);
    static bool save(string filename, PolygonSPtr polygon);
protected:
    FLMAFile();
};

} }

#endif	/* DB_2D_FLMAFILE_H */

