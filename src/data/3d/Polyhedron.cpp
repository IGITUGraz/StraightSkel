/**
 * @file   data/3d/Polyhedron.cpp
 * @author Gernot Walzl
 * @date   2011-11-26
 */

#include "Polyhedron.h"

namespace data { namespace _3d {

Polyhedron::Polyhedron() {
    this->id_ = -1;
}

Polyhedron::~Polyhedron() {
    facets_.clear();
    edges_.clear();
    vertices_.clear();
}

PolyhedronSPtr Polyhedron::create() {
    PolyhedronSPtr result = PolyhedronSPtr(new Polyhedron());
    return result;
}

PolyhedronSPtr Polyhedron::create(unsigned int num_facets, FacetSPtr facets[]) {
    PolyhedronSPtr result = PolyhedronSPtr(new Polyhedron());
    for (unsigned int i = 0; i < num_facets; i++) {
        result->addFacet(facets[i]);
    }
    return result;
}

PolyhedronSPtr Polyhedron::clone() const {
    map<VertexSPtr, VertexSPtr> vertices_c;
    map<EdgeSPtr, EdgeSPtr> edges_c;
    PolyhedronSPtr result = Polyhedron::create();
    result->setDescription(description_);
    list<VertexSPtr>::const_iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        VertexSPtr vertex_c = vertex->clone();
        result->addVertex(vertex_c);
        vertices_c[vertex] = vertex_c;
    }
    list<EdgeSPtr>::const_iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        VertexSPtr src = vertices_c[edge->getVertexSrc()];
        VertexSPtr dst = vertices_c[edge->getVertexDst()];
        EdgeSPtr edge_c = Edge::create(src, dst);
        result->addEdge(edge_c);
        edges_c[edge] = edge_c;
    }
    list<FacetSPtr>::const_iterator it_f = facets_.begin();
    while (it_f != facets_.end()) {
        FacetSPtr facet = *it_f++;
        FacetSPtr facet_c = Facet::create();
        facet_c->setPlane(facet->getPlane());
        list<VertexSPtr>::const_iterator it_v = facet->vertices().begin();
        while (it_v != facet->vertices().end()) {
            VertexSPtr vertex = *it_v++;
            facet_c->addVertex(vertices_c[vertex]);
        }
        list<EdgeSPtr>::const_iterator it_e = facet->edges().begin();
        while (it_e != facet->edges().end()) {
            EdgeSPtr edge = *it_e++;
            EdgeSPtr edge_c = edges_c[edge];
            if (edge->getFacetL() == facet) {
                edge_c->setFacetL(facet_c);
            }
            if (edge->getFacetR() == facet) {
                edge_c->setFacetR(facet_c);
            }
            facet_c->addEdge(edge_c);
        }
        list<TriangleSPtr>::const_iterator it_t = facet->triangles().begin();
        while (it_t != facet->triangles().end()) {
            TriangleSPtr triangle = *it_t++;
            VertexSPtr vertices_t_c[3];
            for (unsigned int i = 0; i < 3; i++) {
                vertices_t_c[i] = vertices_c[triangle->getVertex(i)];
            }
            Triangle::create(facet_c, vertices_t_c);
        }
        result->addFacet(facet_c);
    }
    return result;
}

void Polyhedron::addVertex(VertexSPtr vertex) {
    list<VertexSPtr>::iterator it = vertices_.insert(vertices_.end(), vertex);
    vertex->setPolyhedron(shared_from_this());
    vertex->setPolyhedronListIt(it);
}

bool Polyhedron::removeVertex(VertexSPtr vertex) {
    bool result = false;
    if (vertex->getPolyhedron() == shared_from_this()) {
        vertices_.erase(vertex->getPolyhedronListIt());
        vertex->setPolyhedronListIt(list<VertexSPtr>::iterator());
        vertex->setPolyhedron(PolyhedronSPtr());
        list<FacetWPtr>::iterator it_f = vertex->facets().begin();
        while (it_f != vertex->facets().end()) {
            FacetWPtr facet_wptr = *it_f++;
            if (!facet_wptr.expired()) {
                FacetSPtr facet = FacetSPtr(facet_wptr);
                this->removeFacet(facet);
            }
        }
        list<EdgeWPtr>::iterator it_e = vertex->edges().begin();
        while (it_e != vertex->edges().end()) {
            EdgeWPtr edge_wptr = *it_e++;
            if (!edge_wptr.expired()) {
                EdgeSPtr edge = EdgeSPtr(edge_wptr);
                this->removeEdge(edge);
            }
        }
        result = true;
    }
    return result;
}

VertexSPtr Polyhedron::findVertex(VertexSPtr needle) {
    VertexSPtr result = VertexSPtr();
    list<VertexSPtr>::iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        if (vertex->getPoint() == needle->getPoint()) {
            result = vertex;
            break;
        }
    }
    return result;
}

void Polyhedron::addEdge(EdgeSPtr edge) {
    list<EdgeSPtr>::iterator it = edges_.insert(edges_.end(), edge);
    edge->setPolyhedron(shared_from_this());
    edge->setPolyhedronListIt(it);
    VertexSPtr vertex = edge->getVertexSrc();
    if (vertex->getPolyhedron() != shared_from_this()) {
        this->addVertex(vertex);
    }
    vertex = edge->getVertexDst();
    if (vertex->getPolyhedron() != shared_from_this()) {
        this->addVertex(vertex);
    }
}

bool Polyhedron::removeEdge(EdgeSPtr edge) {
    bool result = false;
    if (edge->getPolyhedron() == shared_from_this()) {
        edges_.erase(edge->getPolyhedronListIt());
        edge->setPolyhedronListIt(list<EdgeSPtr>::iterator());
        edge->setPolyhedron(PolyhedronSPtr());
        FacetSPtr facet = edge->getFacetL();
        if (facet) {
            this->removeFacet(facet);
        }
        facet = edge->getFacetR();
        if (facet) {
            this->removeFacet(facet);
        }
        edge->getVertexSrc()->removeEdge(edge);
        edge->getVertexDst()->removeEdge(edge);
        result = true;
    }
    return result;
}

EdgeSPtr Polyhedron::findEdge(EdgeSPtr needle) {
    EdgeSPtr result = EdgeSPtr();
    list<EdgeSPtr>::iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        if (edge->getVertexSrc()->getPoint() ==
                needle->getVertexSrc()->getPoint() &&
                edge->getVertexDst()->getPoint() ==
                needle->getVertexDst()->getPoint()) {
            result = edge;
            break;
        }
        if (edge->getVertexSrc()->getPoint() ==
                needle->getVertexDst()->getPoint() &&
                edge->getVertexDst()->getPoint() ==
                needle->getVertexSrc()->getPoint()) {
            result = edge;
            break;
        }
    }
    return result;
}

void Polyhedron::addFacet(FacetSPtr facet) {
    list<FacetSPtr>::iterator it_f = facets_.insert(facets_.end(), facet);
    facet->setPolyhedronListIt(it_f);
    facet->setPolyhedron(shared_from_this());
    // add content of facet
    list<VertexSPtr>::iterator it_v = facet->vertices().begin();
    while (it_v != facet->vertices().end()) {
        VertexSPtr vertex = *it_v++;
        if (vertex->getPolyhedron() != shared_from_this()) {
            this->addVertex(vertex);
        }
    }
    list<EdgeSPtr>::iterator it_e = facet->edges().begin();
    while (it_e != facet->edges().end()) {
        EdgeSPtr edge = *it_e++;
        if (edge->getPolyhedron() != shared_from_this()) {
            this->addEdge(edge);
        }
    }
}

bool Polyhedron::removeFacet(FacetSPtr facet) {
    bool result = false;
    if (facet->getPolyhedron() == shared_from_this()) {
        facets_.erase(facet->getPolyhedronListIt());
        facet->setPolyhedron(PolyhedronSPtr());
        facet->setPolyhedronListIt(list<FacetSPtr>::iterator());
        list<EdgeSPtr>::iterator it_e = facet->edges().begin();
        while (it_e != facet->edges().end()) {
            EdgeSPtr edge = *it_e++;
            facet->removeEdge(edge);  // clears list iterators
        }
        list<VertexSPtr>::iterator it_v = facet->vertices().begin();
        while (it_v != facet->vertices().end()) {
            VertexSPtr vertex = *it_v++;
            facet->removeVertex(vertex);
        }
        result = true;
    }
    return result;
}

void Polyhedron::initPlanes() {
    list<FacetSPtr>::iterator it_f = facets_.begin();
    while (it_f != facets_.end()) {
        FacetSPtr facet = *it_f++;
        facet->initPlane();
    }
}

void Polyhedron::clearData() {
    list<VertexSPtr>::iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        vertex->setData(VertexDataSPtr());
    }
    list<EdgeSPtr>::iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        edge->setData(EdgeDataSPtr());
    }
    list<FacetSPtr>::iterator it_f = facets_.begin();
    while (it_f != facets_.end()) {
        FacetSPtr facet = *it_f++;
        facet->setData(FacetDataSPtr());
    }
}

SharedMutex& Polyhedron::mutex() {
    return this->mutex_;
}

list<VertexSPtr>& Polyhedron::vertices() {
    return this->vertices_;
}

list<EdgeSPtr>& Polyhedron::edges() {
    return this->edges_;
}

list<FacetSPtr>& Polyhedron::facets() {
    return this->facets_;
}

bool Polyhedron::isConsistent() const {
    bool result = true;

    list<VertexSPtr>::const_iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        if (vertex->getPolyhedron() != shared_from_this()) {
            DEBUG_VAR(vertex->toString());
            result = false;
            break;
        }
        list<EdgeWPtr>::const_iterator it_e = vertex->edges().begin();
        while (it_e != vertex->edges().end()) {
            EdgeWPtr edge_wptr = *it_e++;
            if (edge_wptr.expired()) {
                DEBUG_VAR(vertex->toString());
            } else {
                EdgeSPtr edge = EdgeSPtr(edge_wptr);
                if (vertex != edge->getVertexSrc() &&
                        vertex != edge->getVertexDst()) {
                    DEBUG_VAR(vertex->toString());
                    DEBUG_VAR(edge->toString());
                    result = false;
                    break;
                }
            }
        }
        list<FacetWPtr>::const_iterator it_f = vertex->facets().begin();
        while (it_f != vertex->facets().end()) {
            FacetWPtr facet_wptr = *it_f++;
            if (facet_wptr.expired()) {
                DEBUG_VAR(vertex->toString());
            } else {
                FacetSPtr facet = FacetSPtr(facet_wptr);
                if (!facet->containsVertex(vertex)) {
                    DEBUG_VAR(vertex->toString());
                    DEBUG_VAR(facet->toString());
                    result = false;
                    break;
                }
            }
        }
    }

    list<EdgeSPtr>::const_iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        if (edge->getPolyhedron() != shared_from_this()) {
            DEBUG_VAR(edge->toString());
            result = false;
            break;
        }
        if (!edge->getVertexSrc()->containsEdge(edge)) {
            DEBUG_VAR(edge->toString());
            DEBUG_VAR(edge->getVertexSrc()->toString());
            result = false;
            break;
        }
        if (!edge->getVertexDst()->containsEdge(edge)) {
            DEBUG_VAR(edge->toString());
            DEBUG_VAR(edge->getVertexDst()->toString());
            result = false;
            break;
        }
        EdgeWPtr edge_wptr;
        edge_wptr = *(edge->getVertexSrcListIt());
        if (EdgeSPtr(edge_wptr) != edge) {
            DEBUG_VAR(edge->toString());
        }
        edge_wptr = *(edge->getVertexDstListIt());
        if (EdgeSPtr(edge_wptr) != edge) {
            DEBUG_VAR(edge->toString());
        }
        if (edge->getFacetL()) {
            if (!edge->getFacetL()->containsEdge(edge)) {
                DEBUG_VAR(edge->toString());
                DEBUG_VAR(edge->getFacetL()->toString());
                result = false;
                break;
            }
            edge_wptr = *(edge->getFacetLListIt());
            if (EdgeSPtr(edge_wptr) != edge) {
                DEBUG_VAR(edge->toString());
            }
        }
        if (edge->getFacetR()) {
            if (!edge->getFacetR()->containsEdge(edge)) {
                DEBUG_VAR(edge->toString());
                DEBUG_VAR(edge->getFacetR()->toString());
                result = false;
                break;
            }
            edge_wptr = *(edge->getFacetRListIt());
            if (EdgeSPtr(edge_wptr) != edge) {
                DEBUG_VAR(edge->toString());
            }
        }
    }

    list<FacetSPtr>::const_iterator it_f = facets_.begin();
    while (it_f != facets_.end()) {
        FacetSPtr facet = *it_f++;
        if (facet->getPolyhedron() != shared_from_this()) {
            DEBUG_VAR(facet->toString());
            result = false;
            break;
        }
        list<VertexSPtr>::const_iterator it_v = facet->vertices().begin();
        while (it_v != facet->vertices().end()) {
            VertexSPtr vertex = *it_v++;
            if (!vertex->containsFacet(facet)) {
                DEBUG_VAR(facet->toString());
                DEBUG_VAR(vertex->toString());
                result = false;
                break;
            }
        }
        list<EdgeSPtr>::const_iterator it_e = facet->edges().begin();
        while (it_e != facet->edges().end()) {
            EdgeSPtr edge = *it_e++;
            if (edge->getFacetL() != facet && edge->getFacetR() != facet) {
                DEBUG_VAR(facet->toString());
                DEBUG_VAR(edge->toString());
                result = false;
                break;
            }
            if (!facet->containsVertex(edge->getVertexSrc()) ||
                    !facet->containsVertex(edge->getVertexDst())) {
                DEBUG_VAR(facet->toString());
                DEBUG_VAR(edge->toString());
                result = false;
                break;
            }
        }
    }

    return result;
}

void Polyhedron::clear() {
    list<FacetSPtr>::iterator it_f = facets_.begin();
    while (it_f != facets_.end()) {
        FacetSPtr facet = *it_f++;
        this->removeFacet(facet);
    }
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

int Polyhedron::getID() const {
    return this->id_;
}

void Polyhedron::setID(int id) {
    this->id_ = id;
}

void Polyhedron::resetAllIDs() {
    list<FacetSPtr>::iterator it_f = facets_.begin();
    while (it_f != facets_.end()) {
        FacetSPtr facet = *it_f++;
        list<TriangleSPtr>::iterator it_t = facet->triangles().begin();
        while (it_t != facet->triangles().end()) {
            TriangleSPtr triangle = *it_t++;
            triangle->setID(-1);
        }
        facet->setID(-1);
    }
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

string Polyhedron::getDescription() const {
    return this->description_;
}

void Polyhedron::setDescription(string desc) {
    this->description_ = desc;
}

void Polyhedron::appendDescription(string desc) {
    this->description_.append(desc);
}

string Polyhedron::toString() const {
    stringstream sstr;
    sstr << "Polyhedron(";
    if (id_ != -1) {
        sstr << "id=" << StringFactory::fromInteger(id_) << ", ";
    } else {
        sstr << StringFactory::fromPointer(this) << ", ";
    }
    sstr << "Vertices:" + StringFactory::fromInteger(vertices_.size()) + ", ";
    sstr << "Edges:" + StringFactory::fromInteger(edges_.size()) + ", ";
    sstr << "Facets:" + StringFactory::fromInteger(facets_.size()) + ",\n";

    list<FacetSPtr>::const_iterator it_f = facets_.begin();
    while (it_f != facets_.end()) {
        FacetSPtr facet = *it_f++;
        sstr << facet->toString() << "\n";
    }
    sstr << ")";

  /*list<EdgeSPtr>::iterator it_e = edges_.begin();
    while (it_e != edges_.end()) {
        EdgeSPtr edge = *it_e++;
        sstr << edge->toString() << "\n";
    }
    list<VertexSPtr>::iterator it_v = vertices_.begin();
    while (it_v != vertices_.end()) {
        VertexSPtr vertex = *it_v++;
        sstr << vertex->toString() << "\n";
    }*/
    return sstr.str();
}

} }
