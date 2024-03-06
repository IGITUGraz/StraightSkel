/**
 * @file   algo/2d/SimpleStraightSkel.h
 * @author Gernot Walzl
 * @date   2012-02-06
 */

#ifndef ALGO_2D_SIMPLESTRAIGHTSKEL_H
#define	ALGO_2D_SIMPLESTRAIGHTSKEL_H

#include <list>
#include "boost_thread.h"
#include "debug.h"
#include "util/Configuration.h"
#include "util/Timer.h"
#include "algo/ptrs.h"
#include "algo/Controller.h"
#include "algo/2d/ptrs.h"
#include "algo/2d/KernelWrapper.h"
#include "data/2d/ptrs.h"
#include "data/2d/Polygon.h"
#include "data/2d/Vertex.h"
#include "data/2d/Edge.h"
#include "data/2d/skel/ptrs.h"
#include "data/2d/skel/StraightSkeleton.h"
#include "data/2d/skel/Node.h"
#include "data/2d/skel/Arc.h"
#include "data/2d/skel/ConstOffsetEvent.h"
#include "data/2d/skel/EdgeEvent.h"
#include "data/2d/skel/SplitEvent.h"
#include "data/2d/skel/TriangleEvent.h"
#include "data/2d/skel/SkelVertexData.h"
#include "data/2d/skel/SkelEdgeData.h"

namespace algo { namespace _2d {

using std::list;
using boost::dynamic_pointer_cast;
using namespace data::_2d;
using namespace data::_2d::skel;

class SimpleStraightSkel {
public:
    virtual ~SimpleStraightSkel();

    static SimpleStraightSkelSPtr create(PolygonSPtr polygon);
    static SimpleStraightSkelSPtr create(PolygonSPtr polygon, ControllerSPtr controller);

    void run();
    ThreadSPtr startThread();

    static NodeSPtr createNode(VertexSPtr vertex);
    static ArcSPtr createArc(VertexSPtr vertex);
    bool init(PolygonSPtr polygon);
    static list<EdgeEventSPtr> nextEdgeEvent(PolygonSPtr polygon, double offset);
    static Point2SPtr crashAt(VertexSPtr vertex, EdgeSPtr edge);
    static list<SplitEventSPtr> nextSplitEvent(PolygonSPtr polygon, double offset);
    static list<AbstractEventSPtr> nextEvent(PolygonSPtr polygon, double offset);

    static PolygonSPtr shiftEdges(PolygonSPtr polygon, double offset);

    void appendEventNode(NodeSPtr node);

    void handleEdgeEvent(EdgeEventSPtr event, PolygonSPtr polygon);
    void handleSplitEvent(SplitEventSPtr event, PolygonSPtr polygon);
    void handleTriangleEvent(TriangleEventSPtr event, PolygonSPtr polygon);

    StraightSkeletonSPtr getResult() const;

protected:
    SimpleStraightSkel(PolygonSPtr polygon);
    SimpleStraightSkel(PolygonSPtr polygon, ControllerSPtr controller);

    PolygonSPtr polygon_;
    ControllerSPtr controller_;
    StraightSkeletonSPtr skel_result_;
};

} }

#endif	/* ALGO_2D_SIMPLESTRAIGHTSKEL_H */

