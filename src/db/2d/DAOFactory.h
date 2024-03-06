/**
 * @file   db/2d/DAOFactory.h
 * @author Gernot Walzl
 * @date   2012-01-27
 */

#ifndef DB_2D_DAOFACTORY_H
#define	DB_2D_DAOFACTORY_H

#include <cstdlib>
#include <string>
#include <fstream>
#include "db/ptrs.h"
#include "db/SQLiteDatabase.h"
#include "db/2d/ptrs.h"
#include "db/2d/PointDAO.h"
#include "db/2d/VertexDAO.h"
#include "db/2d/EdgeDAO.h"
#include "db/2d/PolygonDAO.h"
#include "db/2d/NodeDAO.h"
#include "db/2d/ArcDAO.h"
#include "db/2d/EventDAO.h"
#include "db/2d/StraightSkeletonDAO.h"

namespace db { namespace _2d {

using std::string;

class DAOFactory {
public:
    virtual ~DAOFactory();

    static string findDefaultFilename();
    static bool createTables();
    static SQLiteDatabaseSPtr getDB();

    static PointDAOSPtr getPointDAO();

    static VertexDAOSPtr getVertexDAO();
    static EdgeDAOSPtr getEdgeDAO();
    static PolygonDAOSPtr getPolygonDAO();

    static NodeDAOSPtr getNodeDAO();
    static ArcDAOSPtr getArcDAO();
    static EventDAOSPtr getEventDAO();
    static StraightSkeletonDAOSPtr getStraightSkeletonDAO();

protected:
    DAOFactory();

    static SQLiteDatabaseSPtr db_;

    static PointDAOSPtr point_dao_;

    static VertexDAOSPtr vertex_dao_;
    static EdgeDAOSPtr edge_dao_;
    static PolygonDAOSPtr polygon_dao_;

    static NodeDAOSPtr node_dao_;
    static ArcDAOSPtr arc_dao_;
    static EventDAOSPtr event_dao_;
    static StraightSkeletonDAOSPtr straightskeleton_dao_;
};

} }

#endif	/* DB_2D_DAOFACTORY_H */

