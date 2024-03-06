/**
 * @file   data/2d/Vertex.h
 * @author Gernot Walzl
 * @date   2011-11-22
 */

#ifndef DATA_2D_VERTEX_H
#define	DATA_2D_VERTEX_H

#include <cmath>
#include <list>
#include <string>
#include "debug.h"
#include "util/StringFactory.h"
#include "data/2d/ptrs.h"
#include "data/2d/Edge.h"

namespace data { namespace _2d {

using std::list;
using std::string;
using util::StringFactory;

class Vertex {
public:
    virtual ~Vertex();

    static VertexSPtr create(Point2SPtr point);

    VertexSPtr clone() const;

    Point2SPtr getPoint() const;
    void setPoint(Point2SPtr point);
    EdgeSPtr getEdgeIn() const;
    void setEdgeIn(EdgeSPtr edge);
    EdgeSPtr getEdgeOut() const;
    void setEdgeOut(EdgeSPtr edge);
    PolygonSPtr getPolygon() const;
    void setPolygon(PolygonSPtr polygon);
    list<VertexSPtr>::iterator getListIt() const;
    void setListIt(list<VertexSPtr>::iterator list_it);
    VertexDataSPtr getData() const;
    void setData(VertexDataSPtr data);
    bool hasData() const;

    int getID() const;
    void setID(int id);

    VertexSPtr next() const;
    VertexSPtr prev() const;

    double getX() const;
    double getY() const;

    double angle() const;
    bool isReflex() const;

    string toString() const;

protected:
    Vertex(Point2SPtr point);
    Vertex(const Vertex& vertex);
    Point2SPtr point_;
    EdgeWPtr edge_in_;
    EdgeWPtr edge_out_;
    PolygonWPtr polygon_;
    list<VertexSPtr>::iterator list_it_;
    VertexDataSPtr data_;
    int id_;
};

} }

#endif	/* DATA_2D_VERTEX_H */

