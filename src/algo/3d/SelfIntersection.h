/**
 * @file   algo/3d/SelfIntersection.h
 * @author Gernot Walzl
 * @date   2012-07-18
 */

#ifndef ALGO_3D_SELFINTERSECTION_H
#define	ALGO_3D_SELFINTERSECTION_H

#include <list>
#include <limits>
#include "data/3d/ptrs.h"
#include "data/3d/KernelFactory.h"
#include "data/3d/Edge.h"
#include "data/3d/Facet.h"
#include "algo/3d/KernelWrapper.h"

namespace algo { namespace _3d {

using namespace data::_3d;

class SelfIntersection {
public:
    virtual ~SelfIntersection();

    static Point3SPtr intersectEdges(FacetSPtr facet,
            EdgeSPtr edge1, EdgeSPtr edge2, bool handle_deg1_as_ray);
    static bool isSelfIntersectingFacet(FacetSPtr facet);
    static unsigned int hasSelfIntersectingFacets(PolyhedronSPtr polyhedron);

    static Plane3SPtr bisector(FacetSPtr facet, VertexSPtr vertex);
    static EdgeSPtr findNearestEdge(FacetSPtr facet, Point3SPtr point);
    static bool isEdgeInsideFacet(FacetSPtr facet, EdgeSPtr edge, bool handle_deg1_as_ray);
    static bool hasSelfIntersectingSurface(PolyhedronSPtr polyhedron);

protected:
    SelfIntersection();
};

} }

#endif	/* ALGO_3D_SELFINTERSECTION_H */

