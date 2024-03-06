#ifndef DB_3D_TRIANGLEDAO_H
#define	DB_3D_TRIANGLEDAO_H

#include <string>
#include "data/3d/ptrs.h"
#include "db/ptrs.h"
#include "db/3d/DAOFactory.h"

namespace db { namespace _3d {

using std::string;
using data::_3d::Triangle;
using data::_3d::TriangleSPtr;

class TriangleDAO {
friend class DAOFactory;
public:
    virtual ~TriangleDAO();
    string getTableSchema() const;
    int insert(TriangleSPtr triangle);
    bool del(TriangleSPtr triangle);
    TriangleSPtr find(int polyhedronid, int fid, int tid);
    bool update(TriangleSPtr triangle);
protected:
    TriangleDAO();
    int nextTID(int polyhedronid, int fid);
};

} }

#endif	/* DB_3D_TRIANGLEDAO_H */
