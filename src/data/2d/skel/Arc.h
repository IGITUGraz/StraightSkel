/**
 * @file   data/2d/skel/Arc.h
 * @author Gernot Walzl
 * @date   2012-02-02
 */

#ifndef DATA_2D_SKEL_ARC_H
#define	DATA_2D_SKEL_ARC_H

#include <list>
#include <string>
#include "debug.h"
#include "data/2d/ptrs.h"
#include "data/2d/KernelFactory.h"
#include "data/2d/skel/ptrs.h"
#include "data/2d/skel/Node.h"

namespace data { namespace _2d { namespace skel {

using std::list;
using std::string;

class Arc {
public:
    virtual ~Arc();
    static ArcSPtr create(NodeSPtr node_src, Vector2SPtr direction);
    static ArcSPtr create(NodeSPtr node_src, NodeSPtr node_dst);

    NodeSPtr getNodeSrc() const;
    void setNodeSrc(NodeSPtr node_src);
    list<ArcWPtr>::iterator getNodeSrcListIt() const;
    void setNodeSrcListIt(list<ArcWPtr>::iterator node_src_list_it);
    NodeSPtr getNodeDst() const;
    void setNodeDst(NodeSPtr node_dst);
    list<ArcWPtr>::iterator getNodeDstListIt() const;
    void setNodeDstListIt(list<ArcWPtr>::iterator node_dst_list_it);
    Vector2SPtr getDirection() const;
    void setDirection(Vector2SPtr direction);
    EdgeSPtr getEdgeLeft() const;
    void setEdgeLeft(EdgeSPtr edge_left);
    EdgeSPtr getEdgeRight() const;
    void setEdgeRight(EdgeSPtr edge_right);
    StraightSkeletonSPtr getSkel() const;
    void setSkel(StraightSkeletonSPtr skel);
    list<ArcSPtr>::iterator getListIt() const;
    void setListIt(list<ArcSPtr>::iterator list_it);

    int getID() const;
    void setID(int id);

    Line2SPtr line() const;

    bool hasNodeDst() const;

    string toString() const;

protected:
    Arc(NodeSPtr node_src, Vector2SPtr direction);
    Arc(NodeSPtr node_src, NodeSPtr node_dst);
    NodeSPtr node_src_;
    list<ArcWPtr>::iterator node_src_list_it_;
    NodeSPtr node_dst_;
    list<ArcWPtr>::iterator node_dst_list_it_;
    Vector2SPtr direction_;
    EdgeSPtr edge_left_;
    EdgeSPtr edge_right_;
    StraightSkeletonWPtr skel_;
    list<ArcSPtr>::iterator list_it_;
    int id_;
};

} } }

#endif	/* DATA_2D_SKEL_ARC_H */

