/**
 * @file   data/3d/Vertex.h
 * @author Gernot Walzl
 * @date   2011-11-26
 */

#ifndef DATA_3D_VERTEX_H
#define	DATA_3D_VERTEX_H

#include <list>
#include <string>
#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/Edge.h"
#include "util/StringFactory.h"

namespace data { namespace _3d {

using std::list;
using std::string;
using util::StringFactory;

class Vertex : public boost::enable_shared_from_this<Vertex> {
public:
    virtual ~Vertex();

    static VertexSPtr create(Point3SPtr point);

    VertexSPtr clone() const;

    Point3SPtr getPoint() const;
    void setPoint(Point3SPtr point);

    void addEdge(EdgeSPtr edge);
    bool removeEdge(EdgeSPtr edge);
    EdgeSPtr firstEdge() const;
    EdgeSPtr getEdge(unsigned int i);

    /**
     * Searches for an edge to the given destination.
     * The orientation of the edge is ignored.
     */
    EdgeSPtr findEdge(VertexSPtr dst) const;

    /**
     * A vertex may be adjacent to the same facet more than once.
     * @deprecated
     */
    EdgeSPtr findEdge(FacetSPtr facet) const;

    void addFacet(FacetSPtr facet);
    bool removeFacet(FacetSPtr facet);
    FacetSPtr firstFacet() const;
    FacetSPtr getFacet(unsigned int i);

    bool containsEdge(EdgeSPtr edge) const;
    bool containsFacet(FacetSPtr facet) const;

    void sortEdges();
    void sortFacets();
    void sort();

    PolyhedronSPtr getPolyhedron() const;
    void setPolyhedron(PolyhedronSPtr polyhedron);
    list<VertexSPtr>::iterator getPolyhedronListIt() const;
    void setPolyhedronListIt(list<VertexSPtr>::iterator list_it);

    VertexDataSPtr getData() const;
    void setData(VertexDataSPtr data);
    bool hasData() const;

    list<EdgeWPtr>& edges();
    list<FacetWPtr>& facets();

    VertexSPtr next(FacetSPtr facet) const;
    VertexSPtr prev(FacetSPtr facet) const;

    /**
     * An edge will be created.
     * The destination vertex will be returned.
     */
    VertexSPtr split(FacetSPtr facet_right, FacetSPtr facet_left);

    double getX() const;
    double getY() const;
    double getZ() const;

    int getID() const;
    void setID(int id);

    unsigned int degree() const;

    /**
     * has reflex edges only.
     */
    bool isReflex() const;

    /**
     * has convex edges only.
     */
    bool isConvex() const;

    string toString() const;

protected:
    Vertex(Point3SPtr point);
    Vertex(const Vertex& vertex);
    Point3SPtr point_;
    list<EdgeWPtr> edges_;
    list<FacetWPtr> facets_;
    PolyhedronWPtr polyhedron_;
    list<VertexSPtr>::iterator polyhedron_list_it_;
    VertexDataSPtr data_;
    int id_;
};

} }

#endif	/* DATA_3D_VERTEX_H */

