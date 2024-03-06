/**
 * @file   data/2d/Edge.h
 * @author Gernot Walzl
 * @date   2011-11-22
 */

#ifndef DATA_2D_EDGE_H
#define	DATA_2D_EDGE_H

#include <list>
#include <string>
#include "debug.h"
#include "data/2d/ptrs.h"
#include "data/2d/Vertex.h"
#include "data/2d/KernelFactory.h"

namespace data { namespace _2d {

using std::list;
using std::string;

class Edge {
public:
    virtual ~Edge();

    static EdgeSPtr create(VertexSPtr src, VertexSPtr dst);

    VertexSPtr getVertexSrc() const;
    void setVertexSrc(VertexSPtr src);
    VertexSPtr getVertexDst() const;
    void setVertexDst(VertexSPtr dst);
    PolygonSPtr getPolygon() const;
    void setPolygon(PolygonSPtr polygon);
    list<EdgeSPtr>::iterator getListIt() const;
    void setListIt(list<EdgeSPtr>::iterator list_it);
    EdgeDataSPtr getData() const;
    void setData(EdgeDataSPtr data);
    bool hasData() const;

    int getID() const;
    void setID(int id);

    EdgeSPtr next() const;
    EdgeSPtr prev() const;

    Segment2SPtr segment() const;
    Line2SPtr line() const;

    string toString() const;

protected:
    Edge();

    VertexSPtr vertex_src_;
    VertexSPtr vertex_dst_;
    PolygonWPtr polygon_;
    list<EdgeSPtr>::iterator list_it_;
    EdgeDataSPtr data_;
    int id_;
};

} }

#endif	/* DATA_2D_EDGE_H */

