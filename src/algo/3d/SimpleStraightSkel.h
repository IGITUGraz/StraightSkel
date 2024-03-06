/**
 * @file   algo/3d/SimpleStraightSkel.h
 * @author Gernot Walzl
 * @date   2012-03-08
 */

#ifndef ALGO_3D_SIMPLESTRAIGHTSKEL_H
#define	ALGO_3D_SIMPLESTRAIGHTSKEL_H

#include <list>
#include <stdexcept>
#include <limits>

#include "boost_thread.h"
#include "debug.h"
#include "util/Configuration.h"
#include "util/Timer.h"

#include "data/3d/ptrs.h"
#include "data/3d/Polyhedron.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/StraightSkeleton.h"
#include "data/3d/skel/AbstractEvent.h"
#include "data/3d/skel/ConstOffsetEvent.h"
#include "data/3d/skel/EdgeEvent.h"
#include "data/3d/skel/EdgeMergeEvent.h"
#include "data/3d/skel/TriangleEvent.h"
#include "data/3d/skel/DblEdgeMergeEvent.h"
#include "data/3d/skel/DblTriangleEvent.h"
#include "data/3d/skel/TetrahedronEvent.h"
#include "data/3d/skel/VertexEvent.h"
#include "data/3d/skel/FlipVertexEvent.h"
#include "data/3d/skel/SurfaceEvent.h"
#include "data/3d/skel/PolyhedronSplitEvent.h"
#include "data/3d/skel/SplitMergeEvent.h"
#include "data/3d/skel/EdgeSplitEvent.h"
#include "data/3d/skel/PierceEvent.h"
#include "data/3d/skel/Sheet.h"
#include "data/3d/skel/Arc.h"
#include "data/3d/skel/SkelVertexData.h"
#include "data/3d/skel/SkelEdgeData.h"
#include "data/3d/skel/SkelFacetData.h"

#include "algo/ptrs.h"
#include "algo/Controller.h"
#include "algo/3d/ptrs.h"
#include "algo/3d/KernelWrapper.h"
#include "algo/3d/LineInFacet.h"
#include "algo/3d/SelfIntersection.h"
#include "algo/3d/PolyhedronTransformation.h"
#include "algo/3d/AbstractVertexSplitter.h"
#include "algo/3d/AngleVertexSplitter.h"
#include "algo/3d/CombiVertexSplitter.h"
#include "algo/3d/ConvexVertexSplitter.h"
#include "algo/3d/VolumeVertexSplitter.h"
#include "algo/3d/WeightVertexSplitter.h"
#include "algo/3d/SphereVertexSplitter.h"

namespace algo { namespace _3d {

using std::list;
using boost::dynamic_pointer_cast;
using namespace data::_3d;
using namespace data::_3d::skel;

class SimpleStraightSkel {
public:
    virtual ~SimpleStraightSkel();

    static SimpleStraightSkelSPtr create(PolyhedronSPtr polyhedron);
    static SimpleStraightSkelSPtr create(PolyhedronSPtr polyhedron, ControllerSPtr controller);

    void initVertexSplitter();
    void initEdgeEvent();

    static bool isReflex(EdgeSPtr edge);
    static bool isReflex(VertexSPtr vertex);
    static bool isConvex(VertexSPtr vertex);

    static Line3SPtr line(EdgeSPtr edge);

    void run();
    ThreadSPtr startThread();

    /**
     * All vertices of the input polyhedron have to have a maximum degree of 3.
     * The splitting is done by using the speed during the shrinking process.
     * This works for convex vertices only.
     */
    static void splitConvexVertex(VertexSPtr vertex);

    static void splitReflexVertex(VertexSPtr vertex);

    /**
     * Creates a new node for the vertex data.
     * Used by init(...) only.
     */
    static NodeSPtr createNode(VertexSPtr vertex);

    /**
     * Creates a new arc for the vertex data.
     * The node of the vertex data has to be set before.
     */
    static ArcSPtr createArc(VertexSPtr vertex);

    /**
     * Creates a new sheet for the edge data.
     * The arcs of the vertices have to be set before.
     */
    static SheetSPtr createSheet(EdgeSPtr edge);

    /**
     * Split all vertices with degree > 3 and
     * initializes the data variables of all edges and vertices.
     */
    bool init(PolyhedronSPtr polyhedron);

    /**
     * Checks if the given edge is part of a triangle
     * on the surface of the polyhedron.
     * Used by: nextEdgeEvent, nextTriangleEvent
     */
    static bool isTriangle(FacetSPtr facet, EdgeSPtr edge_begin);

    /**
     * Checks if the given edge is part of a tetrahedron.
     * Used by: nextTriangleEvent, nextTetrahedronEvent
     */
    static bool isTetrahedron(EdgeSPtr edge_begin);

    /**
     * Returns the point where the edge will vanish.
     */
    static Point3SPtr vanishesAt(EdgeSPtr edge);

    /**
     * Returns the point where 2 edges will crash into each other.
     */
    static Point3SPtr crashAt(EdgeSPtr edge_1, EdgeSPtr edge_2);

    /**
     * Returns the offset (time) when the facet will reach the given point.
     */
    static double offsetDist(FacetSPtr facet, Point3SPtr point);

    /**
     * Edge flip event.
     */
    static EdgeEventSPtr nextEdgeEvent(PolyhedronSPtr polyhedron, double offset);

    static EdgeMergeEventSPtr nextEdgeMergeEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * The triangle on the surface vanishes.
     */
    static TriangleEventSPtr nextTriangleEvent(PolyhedronSPtr polyhedron, double offset);

    static DblEdgeMergeEventSPtr nextDblEdgeMergeEvent(PolyhedronSPtr polyhedron, double offset);

    static DblTriangleEventSPtr nextDblTriangleEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * A tetrahedron causes one final event only.
     */
    static TetrahedronEventSPtr nextTetrahedronEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * Two vertices crash into each other.
     */
    static VertexEventSPtr nextVertexEvent(PolyhedronSPtr polyhedron, double offset);

    static FlipVertexEventSPtr nextFlipVertexEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * Split event on the surface.
     * Edges do not need to be reflex.
     */
    static SurfaceEventSPtr nextSurfaceEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * This event occurs when two edges collide.
     * The first edge is always reflex.
     */
    static PolyhedronSplitEventSPtr nextPolyhedronSplitEvent(PolyhedronSPtr polyhedron, double offset);

    static SplitMergeEventSPtr nextSplitMergeEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * This event occurs when two edges collide.
     * The first edge is always reflex.
     */
    static EdgeSplitEventSPtr nextEdgeSplitEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * A reflex vertex reaches a facet.
     */
    static PierceEventSPtr nextPierceEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * Determines the next event.
     */
    static AbstractEventSPtr nextEvent(PolyhedronSPtr polyhedron, double offset);

    /**
     * Creates an offset polyhedron.
     * Negative offset points to the interior of the polyhedron.
     */
    static PolyhedronSPtr shiftFacets(PolyhedronSPtr polyhedron, double offset);

    /**
     * Appends a node of an event to the skeleton.
     * It links all adjacent arcs and sheets to this node.
     */
    void appendEventNode(NodeSPtr node);

    void handleEdgeEvent(EdgeEventSPtr event, PolyhedronSPtr polyhedron);
    void handleEdgeMergeEvent(EdgeMergeEventSPtr event, PolyhedronSPtr polyhedron);
    void handleTriangleEvent(TriangleEventSPtr event, PolyhedronSPtr polyhedron);
    void handleDblEdgeMergeEvent(DblEdgeMergeEventSPtr event, PolyhedronSPtr polyhedron);
    void handleDblTriangleEvent(DblTriangleEventSPtr event, PolyhedronSPtr polyhedron);
    void handleTetrahedronEvent(TetrahedronEventSPtr event, PolyhedronSPtr polyhedron);
    void handleVertexEvent(VertexEventSPtr event, PolyhedronSPtr polyhedron);
    void handleFlipVertexEvent(FlipVertexEventSPtr event, PolyhedronSPtr polyhedron);
    void handleSurfaceEvent(SurfaceEventSPtr event, PolyhedronSPtr polyhedron);
    void handlePolyhedronSplitEvent(PolyhedronSplitEventSPtr event, PolyhedronSPtr polyhedron);
    void handleSplitMergeEvent(SplitMergeEventSPtr event, PolyhedronSPtr polyhedron);
    void handleEdgeSplitEvent(EdgeSplitEventSPtr event, PolyhedronSPtr polyhedron);
    void handlePierceEvent(PierceEventSPtr event, PolyhedronSPtr polyhedron);

    StraightSkeletonSPtr getResult() const;

protected:
    SimpleStraightSkel(PolyhedronSPtr polyhedron);
    SimpleStraightSkel(PolyhedronSPtr polyhedron, ControllerSPtr controller);

    static FacetSPtr getFacetSrc(EdgeSPtr edge);
    static FacetSPtr getFacetDst(EdgeSPtr edge);

    PolyhedronSPtr polyhedron_;
    ControllerSPtr controller_;
    bool use_fast_vertex_splitter_;
    AbstractVertexSplitterSPtr vertex_splitter_;
    int edge_event_;
    StraightSkeletonSPtr skel_result_;
};

} }

#endif	/* ALGO_3D_SIMPLESTRAIGHTSKEL_H */

