/**
 * @file   data/2d/Polygon.cpp
 * @author Gernot Walzl
 * @date   2011-11-22
 */

#include "Polygon.h"

namespace data { namespace _2d {

Polygon::Polygon() {
    this->id_ = -1;
}

Polygon::~Polygon() {
    edges_.clear();
    vertices_.clear();
}

PolygonSPtr Polygon::create() {
    PolygonSPtr result = PolygonSPtr(new Polygon());
    return result;
}

PolygonSPtr Polygon::create(unsigned int num_edges, EdgeSPtr edges[]) {
    PolygonSPtr result = PolygonSPtr(new Polygon());
    for (unsigned int i = 0; i < num_edges; i++) {
        result->addEdge(edges[i]);
    }
    result->sortEdges();
    return result;
}

void Polygon::addVertex(VertexSPtr vertex) {
    list<VertexSPtr>::iterator it = vertices_.insert(vertices_.end(), vertex);
    vertex->setPolygon(shared_from_this());
    vertex->setListIt(it);
}

bool Polygon::removeVertex(VertexSPtr vertex) {
    bool result = false;
    if (vertex->getPolygon() == shared_from_this()) {
        vertices_.erase(vertex->getListIt());
        vertex->setPolygon(PolygonSPtr());
        vertex->setListIt(list<VertexSPtr>::iterator());
        EdgeSPtr edge = vertex->getEdgeIn();
        if (edge) {
            this->removeEdge(edge);
            vertex->setEdgeIn(EdgeSPtr());
        }
        edge = vertex->getEdgeOut();
        if (edge) {
            this->removeEdge(edge);
            vertex->setEdgeOut(EdgeSPtr());
        }
        result = true;
    }
    return result;
}

void Polygon::addEdge(EdgeSPtr edge) {
    list<EdgeSPtr>::iterator it = edges_.insert(edges_.end(), edge);
    edge->setPolygon(shared_from_this());
    edge->setListIt(it);
    VertexSPtr vertex = edge->getVertexSrc();
    if (vertex->getPolygon() != shared_from_this()) {
        this->addVertex(vertex);
    }
    vertex = edge->getVertexDst();
    if (vertex->getPolygon() != shared_from_this()) {
        this->addVertex(vertex);
    }
}

bool Polygon::removeEdge(EdgeSPtr edge) {
    bool result = false;
    if (edge->getPolygon() == shared_from_this()) {
        edges_.erase(edge->getListIt());
        edge->setPolygon(PolygonSPtr());
        edge->setListIt(list<EdgeSPtr>::iterator());
        VertexSPtr vertex = edge->getVertexSrc();
        if (vertex->getEdgeOut() == edge) {
            vertex->setEdgeOut(EdgeSPtr());
        }
        vertex = edge->getVertexDst();
        if (vertex->getEdgeIn() == edge) {
            vertex->setEdgeIn(EdgeSPtr());
        }
        result = true;
    }
    return result;
}

void Polygon::sortEdges() {
    list<EdgeSPtr> temp;
    while (edges_.size() > 0) {
        EdgeSPtr first = EdgeSPtr();
        EdgeSPtr edge = edges_.front();
        while (edge != first) {
            if (!first) {
                first = edge;
            }
            edges_.erase(edge->getListIt());
            temp.push_back(edge);
            edge = edge->getVertexDst()->getEdgeOut();
        }
    }
    edges_.clear();
    list<EdgeSPtr>::iterator it_e = temp.begin();
    while (it_e != temp.end()) {
        EdgeSPtr edge = *it_e++;
        edge->setListIt(edges_.insert(edges_.end(), edge));
    }
}

void Polygon::clear() {
    list<EdgeSPtr>::iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        this->removeEdge(edge);
    }
    list<VertexSPtr>::iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        this->removeVertex(vertex);
    }
}

SharedMutex& Polygon::mutex() {
    return this->mutex_;
}

list<VertexSPtr>& Polygon::vertices() {
    return this->vertices_;
}

list<EdgeSPtr>& Polygon::edges() {
    return this->edges_;
}

int Polygon::getID() const {
    return this->id_;
}

void Polygon::setID(int id) {
    this->id_ = id;
}

void Polygon::resetAllIDs() {
    list<EdgeSPtr>::iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        edge->setID(-1);
    }
    list<VertexSPtr>::iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        vertex->setID(-1);
    }
    setID(-1);
}

bool Polygon::isConsistent() const {
    bool result = true;
    list<VertexSPtr>::const_iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        if (vertex->getPolygon() != shared_from_this()) {
            DEBUG_VAR(vertex->toString());
            result = false;
        }
        if (vertex->getEdgeOut()) {
            if (vertex->getEdgeOut()->getVertexSrc() != vertex) {
                DEBUG_VAR(vertex->toString());
                DEBUG_VAR(vertex->getEdgeOut()->toString());
                result = false;
            }
        }
        if (vertex->getEdgeIn()) {
            if (vertex->getEdgeIn()->getVertexDst() != vertex) {
                DEBUG_VAR(vertex->toString());
                DEBUG_VAR(vertex->getEdgeOut()->toString());
                result = false;
            }
        }
    }
    list<EdgeSPtr>::const_iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        if (edge->getPolygon() != shared_from_this()) {
            DEBUG_VAR(edge->toString());
            result = false;
        }
        if (edge->getVertexSrc()) {
            if (edge->getVertexSrc()->getEdgeOut() != edge) {
                DEBUG_VAR(edge->toString());
                DEBUG_VAR(edge->getVertexSrc()->toString());
                result = false;
            }
        } else {
            DEBUG_VAR(edge->toString());
            result = false;
        }
        if (edge->getVertexDst()) {
            if (edge->getVertexDst()->getEdgeIn() != edge) {
                DEBUG_VAR(edge->toString());
                DEBUG_VAR(edge->getVertexDst()->toString());
                result = false;
            }
        } else {
            DEBUG_VAR(edge->toString());
            result = false;
        }
    }
    return result;
}

int Polygon::countReflex() const {
    int result = 0;
    list<VertexSPtr>::const_iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        if (vertex->isReflex()) {
            result += 1;
        }
    }
    return result;
}

int Polygon::countHoles() const {
    int result = -1;
    EdgeSPtr edge;
    EdgeSPtr edge_prev;
    list<EdgeSPtr>::const_iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        edge = *it_e++;
        if (edge->getVertexSrc()->getEdgeIn() != edge_prev) {
            result += 1;
        }
        edge_prev = edge;
    }
    return result;
}

string Polygon::getDescription() const {
    return this->description_;
}

void Polygon::setDescription(string desc) {
    this->description_ = desc;
}

void Polygon::appendDescription(string desc) {
    this->description_.append(desc);
}

string Polygon::toString() const {
    stringstream sstr;
    sstr << "Polygon(";
    if (id_ != -1) {
        sstr << "id=" << StringFactory::fromInteger(id_) << ", ";
    } else {
        sstr << StringFactory::fromPointer(this) << ", ";
    }
    sstr << "Vertices:" + StringFactory::fromInteger(vertices_.size()) + ", ";
    sstr << "Edges:" + StringFactory::fromInteger(edges_.size()) + ",\n";
    list<VertexSPtr>::const_iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        sstr << "\t" << vertex->toString() << "\n";
    }
    sstr << "\n";
    list<EdgeSPtr>::const_iterator it_e = edges_.begin();
        while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        sstr << "\t" << edge->toString() << "\n";
    }
    sstr << ")\n";
    return sstr.str();
}

} }
