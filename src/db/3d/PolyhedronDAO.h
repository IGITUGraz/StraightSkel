#ifndef DB_3D_POLYHEDRONDAO_H
#define	DB_3D_POLYHEDRONDAO_H

#include <list>
#include <map>
#include "boost_thread.h"
#include "data/3d/ptrs.h"
#include "data/3d/Polyhedron.h"
#include "db/3d/DAOFactory.h"
#include "db/3d/ptrs.h"

namespace db { namespace _3d {

using std::list;
using std::map;
using data::_3d::Polyhedron;
using data::_3d::PolyhedronSPtr;

class PolyhedronDAO {
friend class DAOFactory;
public:
    virtual ~PolyhedronDAO();
    string getTableSchema() const;
    int createPolyhedronID(PolyhedronSPtr polyhedron);
    int insert(PolyhedronSPtr polyhedron);
    bool del(PolyhedronSPtr polyhedron);
    PolyhedronSPtr find(int polyhedronid);
    bool update(PolyhedronSPtr polyhedron);
protected:
    PolyhedronDAO();
    int nextPolyhedronID();
};

} }

#endif	/* DB_3D_POLYHEDRONDAO_H */
