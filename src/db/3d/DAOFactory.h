/**
 * @file   db/3d/DAOFactory.h
 * @author Gernot Walzl
 * @date   2012-01-27
 */

#ifndef DB_3D_DAOFACTORY_H
#define	DB_3D_DAOFACTORY_H

#include <cstdlib>
#include <string>
#include <fstream>
#include "db/ptrs.h"
#include "db/SQLiteDatabase.h"
#include "db/3d/ptrs.h"
#include "db/3d/PointDAO.h"
#include "db/3d/PlaneDAO.h"
#include "db/3d/VertexDAO.h"
#include "db/3d/EdgeDAO.h"
#include "db/3d/TriangleDAO.h"
#include "db/3d/FacetDAO.h"
#include "db/3d/PolyhedronDAO.h"
#include "db/3d/NodeDAO.h"
#include "db/3d/ArcDAO.h"
#include "db/3d/SheetDAO.h"
#include "db/3d/EventDAO.h"
#include "db/3d/StraightSkeletonDAO.h"

namespace db { namespace _3d {

using std::string;

class DAOFactory {
public:
    virtual ~DAOFactory();

    static string findDefaultFilename();
    static bool createTables();
    static SQLiteDatabaseSPtr getDB();

    static PointDAOSPtr getPointDAO();
    static PlaneDAOSPtr getPlaneDAO();

    static VertexDAOSPtr getVertexDAO();
    static EdgeDAOSPtr getEdgeDAO();
    static TriangleDAOSPtr getTriangleDAO();
    static FacetDAOSPtr getFacetDAO();
    static PolyhedronDAOSPtr getPolyhedronDAO();

    static NodeDAOSPtr getNodeDAO();
    static ArcDAOSPtr getArcDAO();
    static SheetDAOSPtr getSheetDAO();
    static EventDAOSPtr getEventDAO();
    static StraightSkeletonDAOSPtr getStraightSkeletonDAO();

protected:
    DAOFactory();

    static SQLiteDatabaseSPtr db_;

    static PointDAOSPtr point_dao_;
    static PlaneDAOSPtr plane_dao_;

    static VertexDAOSPtr vertex_dao_;
    static EdgeDAOSPtr edge_dao_;
    static TriangleDAOSPtr triangle_dao_;
    static FacetDAOSPtr facet_dao_;
    static PolyhedronDAOSPtr polyhedron_dao_;

    static NodeDAOSPtr node_dao_;
    static ArcDAOSPtr arc_dao_;
    static SheetDAOSPtr sheet_dao_;
    static EventDAOSPtr event_dao_;
    static StraightSkeletonDAOSPtr straightskeleton_dao_;
};

} }

#endif	/* DB_3D_DAOFACTORY_H */

