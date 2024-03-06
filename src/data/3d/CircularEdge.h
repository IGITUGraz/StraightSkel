/**
 * @file   data/3d/CircularEdge.h
 * @author Gernot Walzl
 * @date   2012-11-28
 */

#ifndef DATA_3D_CIRCULAREDGE_H
#define	DATA_3D_CIRCULAREDGE_H

#include <list>
#include <string>
#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/KernelFactory.h"
#include "data/3d/CircularVertex.h"
#include "data/3d/SphericalPolygon.h"

namespace data { namespace _3d {

using std::list;
using std::string;

class CircularEdge {
public:
    virtual ~CircularEdge();

    static CircularEdgeSPtr create(CircularVertexSPtr src, CircularVertexSPtr dst);

    CircularVertexSPtr getVertexSrc() const;
    void setVertexSrc(CircularVertexSPtr src);
    CircularVertexSPtr getVertexDst() const;
    void setVertexDst(CircularVertexSPtr dst);
    SphericalPolygonSPtr getPolygon() const;
    void setPolygon(SphericalPolygonSPtr polygon);
    list<CircularEdgeSPtr>::iterator getListIt() const;
    void setListIt(list<CircularEdgeSPtr>::iterator list_it);
    CircularEdgeDataSPtr getData() const;
    void setData(CircularEdgeDataSPtr data);
    bool hasData() const;

    Plane3SPtr getSupportingPlane() const;
    void setSupportingPlane(Plane3SPtr supporting_plane);
    bool initSupportingPlane();
    Plane3SPtr supportingPlane();

    CircularEdgeSPtr next() const;
    CircularEdgeSPtr prev() const;

    string toString() const;

protected:
    CircularEdge(CircularVertexSPtr src, CircularVertexSPtr dst);

    CircularVertexSPtr vertex_src_;
    CircularVertexSPtr vertex_dst_;
    SphericalPolygonWPtr polygon_;
    list<CircularEdgeSPtr>::iterator list_it_;
    CircularEdgeDataSPtr data_;
    Plane3SPtr supporting_plane_;
};

} }

#endif	/* DATA_3D_CIRCULAREDGE_H */

