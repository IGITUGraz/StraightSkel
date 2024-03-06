/**
 * @file   db/2d/PolygonDAO.h
 * @author Gernot Walzl
 * @date   2012-01-27
 */

#ifndef DB_2D_POLYGONDAO_H
#define	DB_2D_POLYGONDAO_H

#include <list>
#include <map>
#include "boost_thread.h"
#include "data/2d/ptrs.h"
#include "data/2d/Polygon.h"
#include "db/ptrs.h"
#include "db/2d/ptrs.h"
#include "db/2d/DAOFactory.h"

namespace db { namespace _2d {

using std::list;
using std::map;
using data::_2d::Polygon;
using data::_2d::PolygonSPtr;

class PolygonDAO {
friend class DAOFactory;
public:
    virtual ~PolygonDAO();
    string getTableSchema() const;
    int createPolyID(PolygonSPtr polygon);
    int insert(PolygonSPtr polygon);
    bool del(PolygonSPtr polygon);
    PolygonSPtr find(int polyid);
    bool update(PolygonSPtr polygon);
protected:
    PolygonDAO();
    int nextPolyID();
};

} }

#endif	/* DB_2D_POLYGONDAO_H */

