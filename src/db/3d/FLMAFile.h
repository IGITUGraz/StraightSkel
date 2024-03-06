/**
 * @file:   db/3d/FLMAFile.h
 * @author: Gernot Walzl
 * @date:   2013-12-16
 */

#ifndef DB_3D_FLMAFILE_H
#define	DB_3D_FLMAFILE_H

#include <string>
#include <fstream>
#include <vector>
#include "util/StringFuncs.h"
#include "util/Configuration.h"
#include "db/3d/AbstractFile.h"

namespace db { namespace _3d {

using std::string;
using std::ifstream;
using std::vector;
using namespace data::_3d;

/**
 * AVL flma file format
 */
class FLMAFile : public AbstractFile {
public:
    virtual ~FLMAFile();
    static PolyhedronSPtr load(string filename);
    static bool save(string filename, PolyhedronSPtr polyhedron);
protected:
    FLMAFile();
};

} }

#endif	/* DB_3D_FLMAFILE_H */

