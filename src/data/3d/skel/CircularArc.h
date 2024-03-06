/**
 * @file   data/3d/skel/CircularArc.h
 * @author Gernot Walzl
 * @date   2012-11-28
 */

#ifndef DATA_3D_SKEL_CIRCULARARC_H
#define	DATA_3D_SKEL_CIRCULARARC_H

#include <list>
#include <string>
#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/KernelFactory.h"
#include "data/3d/CircularEdge.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/CircularNode.h"
#include "data/3d/skel/SphericalSkeleton.h"

namespace data { namespace _3d { namespace skel {

using std::list;
using std::string;

class CircularArc {
public:
    virtual ~CircularArc();

    static CircularArcSPtr create(CircularNodeSPtr node_src, Vector3SPtr direction);
    static CircularArcSPtr create(CircularNodeSPtr node_src, CircularNodeSPtr node_dst);

    CircularNodeSPtr getNodeSrc() const;
    void setNodeSrc(CircularNodeSPtr node_src);
    list<CircularArcWPtr>::iterator getNodeSrcListIt() const;
    void setNodeSrcListIt(list<CircularArcWPtr>::iterator node_src_list_it);
    CircularNodeSPtr getNodeDst() const;
    void setNodeDst(CircularNodeSPtr node_dst);
    list<CircularArcWPtr>::iterator getNodeDstListIt() const;
    void setNodeDstListIt(list<CircularArcWPtr>::iterator node_dst_list_it);
    Vector3SPtr getDirection() const;
    void setDirection(Vector3SPtr direction);
    CircularEdgeSPtr getEdgeLeft() const;
    void setEdgeLeft(CircularEdgeSPtr edge_left);
    CircularEdgeSPtr getEdgeRight() const;
    void setEdgeRight(CircularEdgeSPtr edge_right);
    Plane3SPtr getSupportingPlane() const;
    void setSupportingPlane(Plane3SPtr supporting_plane);
    SphericalSkeletonSPtr getSkel() const;
    void setSkel(SphericalSkeletonSPtr skel);
    list<CircularArcSPtr>::iterator getListIt() const;
    void setListIt(list<CircularArcSPtr>::iterator list_it);

    bool hasNodeDst() const;

    string toString() const;

protected:
    CircularArc(CircularNodeSPtr node_src, Vector3SPtr direction);
    CircularArc(CircularNodeSPtr node_src, CircularNodeSPtr node_dst);
    CircularNodeSPtr node_src_;
    list<CircularArcWPtr>::iterator node_src_list_it_;
    CircularNodeSPtr node_dst_;
    list<CircularArcWPtr>::iterator node_dst_list_it_;
    Vector3SPtr direction_;
    CircularEdgeSPtr edge_left_;
    CircularEdgeSPtr edge_right_;
    Plane3SPtr supporting_plane_;
    SphericalSkeletonWPtr skel_;
    list<CircularArcSPtr>::iterator list_it_;
};

} } }

#endif	/* DATA_3D_SKEL_CIRCULARARC_H */

