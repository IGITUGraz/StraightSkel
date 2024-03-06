/**
 * @file   data/3d/skel/SphericalSkeleton.h
 * @author Gernot Walzl
 * @date   2012-11-28
 */

#ifndef DATA_3D_SKEL_SPHERICALSKELETON_H
#define	DATA_3D_SKEL_SPHERICALSKELETON_H

#include <list>
#include <string>
#include "boost_thread.h"
#include "data/3d/ptrs.h"
#include "data/3d/KernelFactory.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/CircularNode.h"
#include "data/3d/skel/CircularArc.h"
#include "data/3d/skel/SphericalAbstractEvent.h"
#include "data/3d/skel/SphericalEdgeEvent.h"
#include "data/3d/skel/SphericalSplitEvent.h"
#include "data/3d/skel/SphericalTriangleEvent.h"

namespace data { namespace _3d { namespace skel {

using std::list;
using std::string;
using std::stringstream;
using boost::dynamic_pointer_cast;

class SphericalSkeleton : public boost::enable_shared_from_this<SphericalSkeleton> {
public:
    virtual ~SphericalSkeleton();

    static SphericalSkeletonSPtr create(Sphere3SPtr sphere);

    Sphere3SPtr getSphere() const;

    Plane3SPtr getRotAxesPlane() const;
    void setRotAxesPlane(Plane3SPtr rot_axes_plane);

    /**
     * also adds the node
     */
    void addEvent(SphericalAbstractEventSPtr event);
    bool removeEvent(SphericalAbstractEventSPtr event);
    void addNode(CircularNodeSPtr node);
    bool removeNode(CircularNodeSPtr node);
    void addArc(CircularArcSPtr arc);
    bool removeArc(CircularArcSPtr arc);

    SharedMutex& mutex();
    list<SphericalAbstractEventSPtr>& events();
    list<CircularNodeSPtr>& nodes();
    list<CircularArcSPtr>& arcs();

    bool isConsistent() const;

    int countEvents(int type) const;

    double getRadius() const;

    string toString() const;

protected:
    SphericalSkeleton(Sphere3SPtr sphere);
    Sphere3SPtr sphere_;
    Plane3SPtr rot_axes_plane_;
    mutable SharedMutex mutex_;
    list<SphericalAbstractEventSPtr> events_;
    list<CircularNodeSPtr> nodes_;
    list<CircularArcSPtr> arcs_;
};

} } }

#endif	/* DATA_3D_SKEL_SPHERICALSKELETON_H */

