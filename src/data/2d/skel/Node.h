/**
 * @file   data/2d/skel/Node.h
 * @author Gernot Walzl
 * @date   2012-02-03
 */

#ifndef DATA_2D_SKEL_NODE_H
#define	DATA_2D_SKEL_NODE_H

#include <list>
#include <string>
#include "debug.h"
#include "data/2d/ptrs.h"
#include "data/2d/skel/ptrs.h"
#include "data/2d/skel/Arc.h"
#include "util/StringFactory.h"

namespace data { namespace _2d { namespace skel {

using std::list;
using std::string;
using util::StringFactory;

class Node : public boost::enable_shared_from_this<Node> {
public:
    virtual ~Node();
    static NodeSPtr create(Point2SPtr point);

    Point2SPtr getPoint() const;
    void setPoint(Point2SPtr point);
    double getHeight() const;
    void setHeight(double height);
    StraightSkeletonSPtr getSkel() const;
    void setSkel(StraightSkeletonSPtr skel);
    list<NodeSPtr>::iterator getListIt() const;
    void setListIt(list<NodeSPtr>::iterator list_it);

    int getID() const;
    void setID(int id);

    void addArc(ArcSPtr arc);
    bool removeArc(ArcSPtr arc);

    list<ArcWPtr>& arcs();

    unsigned int degree() const;

    double getX() const;
    double getY() const;

    string toString() const;

protected:
    Node(Point2SPtr point);
    Point2SPtr point_;
    double height_;
    StraightSkeletonWPtr skel_;
    list<NodeSPtr>::iterator list_it_;
    list<ArcWPtr> arcs_;
    int id_;
};

} } }

#endif	/* DATA_2D_SKEL_NODE_H */

