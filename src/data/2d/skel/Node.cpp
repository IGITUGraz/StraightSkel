/**
 * @file   data/2d/skel/Node.cpp
 * @author Gernot Walzl
 * @date   2012-02-03
 */

#include "Node.h"

namespace data { namespace _2d { namespace skel {

Node::Node(Point2SPtr point) {
    height_ = 0.0;
    point_ = point;
    id_ = -1;
}

Node::~Node() {
    point_.reset();
}

NodeSPtr Node::create(Point2SPtr point) {
    NodeSPtr result = NodeSPtr(new Node(point));
    return result;
}

Point2SPtr Node::getPoint() const {
    DEBUG_SPTR(point_);
    return point_;
}

void Node::setPoint(Point2SPtr point) {
    this->point_ = point;
}

double Node::getHeight() const {
    return height_;
}

void Node::setHeight(double height) {
    this->height_ = height;
}

StraightSkeletonSPtr Node::getSkel() const {
    DEBUG_WPTR(skel_);
    if (this->skel_.expired())
        return StraightSkeletonSPtr();
    else
        return StraightSkeletonSPtr(this->skel_);
}

void Node::setSkel(StraightSkeletonSPtr skel) {
    this->skel_ = skel;
}

list<NodeSPtr>::iterator Node::getListIt() const {
    return this->list_it_;
}

void Node::setListIt(list<NodeSPtr>::iterator list_it) {
    this->list_it_ = list_it;
}

int Node::getID() const {
    return this->id_;
}

void Node::setID(int id) {
    this->id_ = id;
}

void Node::addArc(ArcSPtr arc) {
    list<ArcWPtr>::iterator it = arcs_.insert(arcs_.end(), ArcWPtr(arc));
    if (arc->getNodeSrc() == shared_from_this()) {
        arc->setNodeSrcListIt(it);
    } else if (arc->hasNodeDst()) {
        if (arc->getNodeDst() == shared_from_this()) {
            arc->setNodeDstListIt(it);
        }
    }
}

bool Node::removeArc(ArcSPtr arc) {
    bool result = false;
    if (arc->getNodeSrc() == shared_from_this()) {
        arcs_.erase(arc->getNodeSrcListIt());
        arc->setNodeSrcListIt(list<ArcWPtr>::iterator());
        result = true;
    } else if (arc->hasNodeDst()) {
        if (arc->getNodeDst() == shared_from_this()) {
            arcs_.erase(arc->getNodeDstListIt());
            arc->setNodeDstListIt(list<ArcWPtr>::iterator());
            result = true;
        }
    }
    return result;
}

list<ArcWPtr>& Node::arcs() {
    return this->arcs_;
}

unsigned int Node::degree() const {
    unsigned int result = 0;
    list<ArcWPtr>::const_iterator it_a = arcs_.begin();
    while (it_a != arcs_.end()) {
        ArcWPtr arc_wptr = *it_a++;
        if (!arc_wptr.expired()) {
            result++;
        }
    }
    return result;
}

double Node::getX() const {
#ifdef USE_CGAL
    return this->point_->x();
#else
    return this->point_->getX();
#endif
}

double Node::getY() const {
#ifdef USE_CGAL
    return this->point_->y();
#else
    return this->point_->getY();
#endif
}

string Node::toString() const {
    string result("Node(");
    if (id_ != -1) {
        result += "id=" + StringFactory::fromInteger(id_) + ", ";
    } else {
        result += StringFactory::fromPointer(this) + ", ";
    }
    result += "<" + StringFactory::fromDouble(getX()) + ", ";
    result += StringFactory::fromDouble(getY()) + ">)";
    return result;
}

} } }
