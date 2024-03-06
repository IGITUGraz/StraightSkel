/**
 * @file   data/3d/SphericalPolygon.h
 * @author Gernot Walzl
 * @date   2012-11-28
 */

#ifndef DATA_3D_SPHERICALPOLYGON_H
#define	DATA_3D_SPHERICALPOLYGON_H

#include <list>
#include <map>
#include <string>
#include <sstream>
#include "boost_thread.h"
#include "data/3d/ptrs.h"
#include "data/3d/CircularVertex.h"
#include "data/3d/CircularEdge.h"

namespace data { namespace _3d {

using std::list;
using std::map;
using std::string;
using std::stringstream;

class SphericalPolygon : public boost::enable_shared_from_this<SphericalPolygon> {
public:
    virtual ~SphericalPolygon();

    static SphericalPolygonSPtr create(Sphere3SPtr sphere);
    static SphericalPolygonSPtr create(Sphere3SPtr sphere,
            unsigned int num_edges, CircularEdgeSPtr edges[]);

    SphericalPolygonSPtr clone() const;

    Sphere3SPtr getSphere() const;

    void addVertex(CircularVertexSPtr vertex);
    bool removeVertex(CircularVertexSPtr vertex);
    void addEdge(CircularEdgeSPtr edge);
    bool removeEdge(CircularEdgeSPtr edge);

    void clear();

    SharedMutex& mutex();
    list<CircularVertexSPtr>& vertices();
    list<CircularEdgeSPtr>& edges();

    bool isConsistent() const;

    double getRadius() const;

    string toString() const;

protected:
    SphericalPolygon(Sphere3SPtr sphere);
    mutable SharedMutex mutex_;
    Sphere3SPtr sphere_;
    list<CircularVertexSPtr> vertices_;
    list<CircularEdgeSPtr> edges_;
};

} }

#endif	/* DATA_3D_SPHERICALPOLYGON_H */

