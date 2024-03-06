#ifndef DB_3D_FACETDAO_H
#define	DB_3D_FACETDAO_H

#include <list>
#include <map>
#include "data/3d/ptrs.h"
#include "data/3d/Facet.h"
#include "db/3d/DAOFactory.h"
#include "db/3d/ptrs.h"

namespace db { namespace _3d {

using std::list;
using std::map;
using data::_3d::Facet;
using data::_3d::FacetSPtr;

class FacetDAO {
friend class DAOFactory;
public:
    virtual ~FacetDAO();
    string getTableSchema() const;
    int createFID(FacetSPtr facet);
    int insert(FacetSPtr facet);
    bool del(FacetSPtr facet);
    FacetSPtr find(int polyhedronid, int fid);
    bool update(FacetSPtr facet);
protected:
    FacetDAO();
    int nextFID(int polyhedronid);
};

} }

#endif	/* DB_3D_FACETDAO_H */

