/**
 * @file   algo/3d/GraphChecker.h
 * @author Gernot Walzl
 * @date   2015-11-04
 */

#ifndef ALGO_3D_GRAPHCHECKER_H
#define	ALGO_3D_GRAPHCHECKER_H

#include <list>
#include <set>
#include "data/3d/ptrs.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/StraightSkeleton.h"
#include "data/3d/skel/AbstractEvent.h"
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
#include "algo/3d/ptrs.h"

namespace algo { namespace _3d {

using std::list;
using std::set;
using namespace data::_3d;
using namespace data::_3d::skel;

class GraphChecker {
public:
    virtual ~GraphChecker();

    static GraphCheckerSPtr create();

    NodeSPtr getNode(AbstractEventSPtr event);
    AbstractEventSPtr findEvent(StraightSkeletonSPtr skel, NodeSPtr node);
    unsigned int countVisitedChilds(const set<NodeSPtr>& visited, NodeSPtr node);

    bool check(StraightSkeletonSPtr skel);

protected:
    GraphChecker();
};

} }

#endif	/* ALGO_3D_GRAPHCHECKER_H */

