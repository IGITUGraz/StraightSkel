/**
 * @file   algo/3d/SpeedSimpleSphericalSkel.h
 * @author Gernot Walzl
 * @date   2013-09-04
 */

#ifndef ALGO_3D_SPEEDSIMPLESPHERICALSKEL_H
#define	ALGO_3D_SPEEDSIMPLESPHERICALSKEL_H

#include <list>
#include "boost_thread.h"
#include "debug.h"

#include "util/Configuration.h"

#include "data/3d/ptrs.h"
#include "data/3d/SphericalPolygon.h"
#include "data/3d/CircularVertex.h"
#include "data/3d/CircularEdge.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/SphericalSkeleton.h"
#include "data/3d/skel/CircularNode.h"
#include "data/3d/skel/CircularArc.h"
#include "data/3d/skel/SphericalAbstractEvent.h"
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

class SpeedSimpleSphericalSkel : public AbstractSimpleSphericalSkel {
public:
    virtual ~SpeedSimpleSphericalSkel();

    static SpeedSimpleSphericalSkelSPtr create(SphericalPolygonSPtr polygon);
    static SpeedSimpleSphericalSkelSPtr create(SphericalPolygonSPtr polygon, ControllerSPtr controller);

    virtual void run();

    virtual bool isReflex(CircularVertexSPtr vertex);

    virtual bool init(SphericalPolygonSPtr polygon);

    void initSpeeds(SphericalPolygonSPtr polygon);

    double speed(CircularVertexSPtr vertex);

    static Point3SPtr vanishesAt(CircularEdgeSPtr edge);
    static Point3SPtr crashAt(CircularVertexSPtr vertex, CircularEdgeSPtr edge);

    double offsetTo(CircularVertexSPtr vertex, Point3SPtr point);

    SphericalEdgeEventSPtr nextEdgeEvent(SphericalPolygonSPtr polygon);
    SphericalSplitEventSPtr nextSplitEvent(SphericalPolygonSPtr polygon);
    SphericalTriangleEventSPtr nextTriangleEvent(SphericalPolygonSPtr polygon);

    SphericalAbstractEventSPtr nextEvent(SphericalPolygonSPtr polygon);

    SphericalPolygonSPtr copyPolygon(SphericalPolygonSPtr polygon);

    void handleEdgeEvent(SphericalEdgeEventSPtr event, SphericalPolygonSPtr polygon);
    void handleSplitEvent(SphericalSplitEventSPtr event, SphericalPolygonSPtr polygon);
    void handleTriangleEvent(SphericalTriangleEventSPtr event, SphericalPolygonSPtr polygon);

protected:
    SpeedSimpleSphericalSkel(SphericalPolygonSPtr polygon);
    SpeedSimpleSphericalSkel(SphericalPolygonSPtr polygon, ControllerSPtr controller);
};

} }

#endif	/* ALGO_3D_SPEEDSIMPLESPHERICALSKEL_H */

