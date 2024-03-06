/**
 * @file   data/3d/skel/Sheet.cpp
 * @author Gernot Walzl
 * @date   2012-03-27
 */

#include "Sheet.h"

namespace data { namespace _3d { namespace skel {

Sheet::Sheet() {
    id_ = -1;
}

Sheet::~Sheet() {
    facet_b_.reset();
    facet_f_.reset();
}

SheetSPtr Sheet::create() {
    SheetSPtr result = SheetSPtr(new Sheet());
    return result;
}

FacetSPtr Sheet::getFacetB() const {
    DEBUG_SPTR(facet_b_);
    return facet_b_;
}

void Sheet::setFacetB(FacetSPtr facet_b) {
    facet_b_ = facet_b;
}

FacetSPtr Sheet::getFacetF() const {
    DEBUG_SPTR(facet_f_);
    return facet_f_;
}

void Sheet::setFacetF(FacetSPtr facet_f) {
    facet_f_ = facet_f;
}

StraightSkeletonSPtr Sheet::getSkel() const {
    DEBUG_WPTR(skel_);
    if (this->skel_.expired())
        return StraightSkeletonSPtr();
    else
        return StraightSkeletonSPtr(this->skel_);
}

void Sheet::setSkel(StraightSkeletonSPtr skel) {
    this->skel_ = skel;
}

list<SheetSPtr>::iterator Sheet::getListIt() const {
    return this->list_it_;
}

void Sheet::setListIt(list<SheetSPtr>::iterator list_it) {
    this->list_it_ = list_it;
}

int Sheet::getID() const {
    return this->id_;
}

void Sheet::setID(int id) {
    this->id_ = id;
}

Plane3SPtr Sheet::getPlane() const {
    DEBUG_SPTR(this->plane_);
    return this->plane_;
}

void Sheet::setPlane(Plane3SPtr plane) {
    this->plane_ = plane;
}

void Sheet::addNode(NodeSPtr node) {
    list<NodeSPtr>::iterator it = nodes_.insert(nodes_.end(), node);
    if (!node->containsSheet(shared_from_this())) {
        node->addSheet(shared_from_this());
    }
}

bool Sheet::removeNode(NodeSPtr node) {
    bool result = false;
    nodes_.remove(node);
    result = node->removeSheet(shared_from_this());
    return result;
}

void Sheet::addArc(ArcSPtr arc) {
    list<ArcSPtr>::iterator it = arcs_.insert(arcs_.end(), arc);
    arc->addSheet(shared_from_this());
}

bool Sheet::removeArc(ArcSPtr arc) {
    bool result = false;
    arcs_.remove(arc);
    result = arc->removeSheet(shared_from_this());
    return result;
}

list<ArcSPtr>& Sheet::arcs() {
    return this->arcs_;
}

list<NodeSPtr>& Sheet::nodes() {
    return this->nodes_;
}

string Sheet::toString() const {
    stringstream result;
    result << "Sheet(";
    if (id_ != -1) {
        result << "id=" + StringFactory::fromInteger(id_) << ", ";
    } else {
        result << StringFactory::fromPointer(this) << ", ";
    }
    result << "nodes:" << nodes_.size() << ", ";
    result << "arcs:" << arcs_.size() << ")";
    return result.str();
}

} } }
