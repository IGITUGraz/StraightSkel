/**
 * @file   data/3d/skel/CircularNode.h
 * @author Gernot Walzl
 * @date   2012-11-28
 */

#ifndef DATA_3D_SKEL_CIRCULARNODE_H
#define	DATA_3D_SKEL_CIRCULARNODE_H

#include <list>
#include <string>
#include "debug.h"
#include "util/StringFactory.h"
#include "data/3d/ptrs.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/CircularArc.h"

namespace data { namespace _3d { namespace skel {

using std::list;
using std::string;
using util::StringFactory;

class CircularNode : public boost::enable_shared_from_this<CircularNode> {
public:
    virtual ~CircularNode();

    static CircularNodeSPtr create(Point3SPtr point);

    Point3SPtr getPoint() const;
    void setPoint(Point3SPtr point);

    double getOffset() const;
    void setOffset(double offset);

    SphericalSkeletonSPtr getSkel() const;
    void setSkel(SphericalSkeletonSPtr skel);
    list<CircularNodeSPtr>::iterator getListIt() const;
    void setListIt(list<CircularNodeSPtr>::iterator list_it);

    void addArc(CircularArcSPtr arc);
    bool removeArc(CircularArcSPtr arc);
    bool containsArc(CircularArcSPtr arc) const;

    void clear();

    list<CircularArcWPtr>& arcs();

    unsigned int degree();

    double getX() const;
    double getY() const;
    double getZ() const;

    string toString() const;

protected:
    CircularNode(Point3SPtr point);
    Point3SPtr point_;
    double offset_;
    list<CircularArcWPtr> arcs_;  // every CircularNode has 3 CircularArcs
    SphericalSkeletonWPtr skel_;
    list<CircularNodeSPtr>::iterator list_it_;
};

} } }

#endif	/* DATA_3D_SKEL_CIRCULARNODE_H */

