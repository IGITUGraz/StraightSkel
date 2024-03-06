/**
 * @file   data/2d/Polygon.h
 * @author Gernot Walzl
 * @date   2011-11-22
 */

#ifndef DATA_2D_POLYGON_H
#define	DATA_2D_POLYGON_H

#include <list>
#include <string>
#include "boost_thread.h"
#include "data/2d/ptrs.h"
#include "data/2d/Vertex.h"
#include "data/2d/Edge.h"

namespace data { namespace _2d {

using std::list;
using std::string;
using std::stringstream;

class Polygon : public boost::enable_shared_from_this<Polygon> {
public:
    virtual ~Polygon();

    static PolygonSPtr create();

    /**
     * The left side of the edges point to the interior of the polygon.
     * The edges of the border are oriented counter-clockwise.
     * Holes inside the polygon are oriented clockwise.
     */
    static PolygonSPtr create(unsigned int num_edges, EdgeSPtr edges[]);

    void addVertex(VertexSPtr vertex);
    bool removeVertex(VertexSPtr vertex);
    void addEdge(EdgeSPtr edge);
    bool removeEdge(EdgeSPtr edge);
    void sortEdges();
    void clear();

    SharedMutex& mutex();
    list<VertexSPtr>& vertices();
    list<EdgeSPtr>& edges();

    int getID() const;
    void setID(int id);

    void resetAllIDs();

    bool isConsistent() const;
    int countReflex() const;

    /**
     * Edges have to be sorted before holes can be counted.
     */
    int countHoles() const;

    string getDescription() const;
    void setDescription(string desc);
    void appendDescription(string desc);

    string toString() const;

protected:
    Polygon();
    mutable SharedMutex mutex_;
    list<VertexSPtr> vertices_;
    list<EdgeSPtr> edges_;
    int id_;
    string description_;
};

} }

#endif	/* DATA_2D_POLYGON_H */

