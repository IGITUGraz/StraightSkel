/**
 * @file   data/3d/Polyhedron.h
 * @author Gernot Walzl
 * @date   2011-11-26
 */

#ifndef DATA_3D_POLYHEDRON_H
#define	DATA_3D_POLYHEDRON_H

#include <list>
#include <map>
#include <string>
#include "boost_thread.h"
#include "data/3d/ptrs.h"
#include "data/3d/Vertex.h"
#include "data/3d/Edge.h"
#include "data/3d/Facet.h"
#include "debug.h"

namespace data { namespace _3d {

using std::list;
using std::map;
using std::string;

class Polyhedron : public boost::enable_shared_from_this<Polyhedron> {
public:
    virtual ~Polyhedron();

    static PolyhedronSPtr create();
    static PolyhedronSPtr create(unsigned int num_facets, FacetSPtr facets[]);

    PolyhedronSPtr clone() const;

    void addVertex(VertexSPtr vertex);
    bool removeVertex(VertexSPtr vertex);

    /**
     * Searches for a vertex with the same coordinates as the given vertex.
     */
    VertexSPtr findVertex(VertexSPtr needle);

    void addEdge(EdgeSPtr edge);
    bool removeEdge(EdgeSPtr edge);

    /**
     * Searches for an edge with the same coordinates as the given edge.
     * The orientation of the edge is ignored.
     */
    EdgeSPtr findEdge(EdgeSPtr needle);

    void addFacet(FacetSPtr facet);
    bool removeFacet(FacetSPtr facet);

    void initPlanes();
    void clearData();

    SharedMutex& mutex();

    list<VertexSPtr>& vertices();
    list<EdgeSPtr>& edges();
    list<FacetSPtr>& facets();

    bool isConsistent() const;
    void clear();

    int getID() const;
    void setID(int id);

    void resetAllIDs();

    string getDescription() const;
    void setDescription(string desc);
    void appendDescription(string desc);

    string toString() const;

protected:
    Polyhedron();
    mutable SharedMutex mutex_;
    list<VertexSPtr> vertices_;
    list<EdgeSPtr> edges_;
    list<FacetSPtr> facets_;
    int id_;
    string description_;
};

} }

#endif	/* DATA_3D_POLYHEDRON_H */

