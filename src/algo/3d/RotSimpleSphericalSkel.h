/**
 * @file   algo/3d/RotSimpleSphericalSkel.h
 * @author Gernot Walzl
 * @date   2012-12-28
 */

#ifndef ALGO_3D_ROTSIMPLESPHERICALSKEL_H
#define	ALGO_3D_ROTSIMPLESPHERICALSKEL_H

#include <list>
#include <limits>
#include "boost_thread.h"
#include "debug.h"

#include "util/Configuration.h"

#include "data/3d/ptrs.h"
#include "data/3d/KernelFactory.h"
#include "data/3d/SphericalPolygon.h"
#include "data/3d/CircularVertex.h"
#include "data/3d/CircularEdge.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/SphericalSkeleton.h"
#include "data/3d/skel/CircularNode.h"
#include "data/3d/skel/CircularArc.h"
#include "data/3d/skel/SphericalAbstractEvent.h"
#include "data/3d/skel/SphericalConstOffsetEvent.h"
#include "data/3d/skel/SphericalEdgeEvent.h"
#include "data/3d/skel/SphericalSplitEvent.h"
#include "data/3d/skel/SphericalTriangleEvent.h"

#include "algo/ptrs.h"
#include "algo/Controller.h"
#include "algo/3d/ptrs.h"
#include "algo/3d/AbstractSimpleSphericalSkel.h"
#include "algo/3d/KernelWrapper.h"

namespace algo { namespace _3d {

using std::list;
using boost::dynamic_pointer_cast;
using namespace data::_3d;
using namespace data::_3d::skel;

class RotSimpleSphericalSkel : public AbstractSimpleSphericalSkel {
public:
    virtual ~RotSimpleSphericalSkel();

    static RotSimpleSphericalSkelSPtr create(SphericalPolygonSPtr polygon);
    static RotSimpleSphericalSkelSPtr create(SphericalPolygonSPtr polygon, ControllerSPtr controller);

    virtual void run();

    virtual bool isReflex(CircularVertexSPtr vertex);

    virtual bool init(SphericalPolygonSPtr polygon);

    void initSpeeds(SphericalPolygonSPtr polygon);
    void updateSpeeds(SphericalPolygonSPtr polygon_prev);

    static double approxOffsetTo(CircularVertexSPtr vertex, Point3SPtr point);

    SphericalEdgeEventSPtr nextEdgeEvent(SphericalPolygonSPtr polygon, double offset);
    SphericalSplitEventSPtr nextSplitEvent(SphericalPolygonSPtr polygon, double offset);
    SphericalTriangleEventSPtr nextTriangleEvent(SphericalPolygonSPtr polygon, double offset);

    SphericalAbstractEventSPtr nextEvent(SphericalPolygonSPtr polygon, double offset);

    CircularEdgeSPtr findLongestEdge(list<CircularEdgeSPtr> edges);

    double distanceOffset(CircularEdgeSPtr edge_begin, double offset, double speed_dst);
    double findMinDistance(CircularEdgeSPtr edge_begin, double offset);

    SphericalPolygonSPtr shiftEdges(SphericalPolygonSPtr polygon, double offset);
    SphericalPolygonSPtr shiftEdges2(SphericalPolygonSPtr polygon, double offset);

    void checkAngles(SphericalPolygonSPtr polygon);

    void handleEdgeEvent(SphericalEdgeEventSPtr event, SphericalPolygonSPtr polygon);
    void handleSplitEvent(SphericalSplitEventSPtr event, SphericalPolygonSPtr polygon);
    void handleTriangleEvent(SphericalTriangleEventSPtr event, SphericalPolygonSPtr polygon);

protected:
    RotSimpleSphericalSkel(SphericalPolygonSPtr polygon);
    RotSimpleSphericalSkel(SphericalPolygonSPtr polygon, ControllerSPtr controller);
};

} }

#endif	/* ALGO_3D_ROTSIMPLESPHERICALSKEL_H */

