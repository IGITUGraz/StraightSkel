/**
 * @file   db/3d/OBJFile.h
 * @author Gernot Walzl
 * @date   2012-05-15
 */

#ifndef DB_3D_OBJFILE_H
#define	DB_3D_OBJFILE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include "util/StringFuncs.h"
#include "util/Configuration.h"
#include "db/3d/AbstractFile.h"

namespace db { namespace _3d {

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using namespace data::_3d;

/**
 * Wavefront obj file format
 */
class OBJFile : public AbstractFile {
public:
    virtual ~OBJFile();

    static PolyhedronSPtr load(string filename);

    /**
     * It is impossible for an obj file to store holes inside a facet.
     */
    static bool save(string filename, PolyhedronSPtr polyhedron);

protected:
    OBJFile();
};

} }

#endif	/* DB_3D_OBJFILE_H */

