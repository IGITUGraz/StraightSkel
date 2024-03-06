/**
 * @file   algo/3d/PolyhedronIntersection.h
 * @author Gernot Walzl
 * @date   2012-09-26
 */

#ifndef ALGO_3D_POLYHEDRONINTERSECTION_H
#define	ALGO_3D_POLYHEDRONINTERSECTION_H

#include <cmath>
#include <list>
#include <limits>
#include "data/3d/ptrs.h"
#include "data/3d/KernelFactory.h"
#include "data/3d/Edge.h"
#include "data/3d/Facet.h"
#include "data/3d/Polyhedron.h"
#include "data/3d/skel/SkelEdgeData.h"
#include "algo/3d/KernelWrapper.h"
#include "data/2d/ptrs.h"
#include "data/2d/Edge.h"
#include "data/2d/Polygon.h"
#include "data/2d/skel/SkelEdgeData.h"

namespace algo { namespace _3d {

using std::list;
using std::numeric_limits;
using boost::dynamic_pointer_cast;
using namespace data::_3d;

class PolyhedronIntersection {
public:
    virtual ~PolyhedronIntersection();

    static Point3SPtr intersect(EdgeSPtr edge, Plane3SPtr plane);
    static EdgeSPtr findDst(FacetSPtr facet, EdgeSPtr edge_src,
            Plane3SPtr plane);
    static FacetSPtr intersect(PolyhedronSPtr polyhedron, Plane3SPtr plane);

    static data::_2d::PolygonSPtr toWeighted2d(FacetSPtr facet);

protected:
    PolyhedronIntersection();
};

} }

#endif	/* ALGO_3D_POLYHEDRONINTERSECTION_H */

