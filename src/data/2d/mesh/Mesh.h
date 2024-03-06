/**
 * @file   data/2d/mesh/Mesh.h
 * @author Gernot Walzl
 * @date   2014-01-24
 */

#ifndef DATA_2D_MESH_MESH_H
#define	DATA_2D_MESH_MESH_H

#include <list>
#include <map>
#include <string>
#include "debug.h"
#include "boost_thread.h"
#include "util/StringFactory.h"
#include "data/2d/ptrs.h"
#include "data/2d/mesh/ptrs.h"
#include "data/2d/mesh/MeshVertex.h"
#include "data/2d/mesh/MeshCell.h"
#include "data/2d/mesh/MeshRay.h"

namespace data { namespace _2d { namespace mesh {

using std::list;
using std::map;
using std::string;
using std::stringstream;
using util::StringFactory;

class Mesh : public boost::enable_shared_from_this<Mesh> {
public:
    virtual ~Mesh();
    static MeshSPtr create();

    bool addVertex(MeshVertexSPtr vertex);
    bool removeVertex(MeshVertexSPtr vertex);
    MeshVertexSPtr getVertex(Point2SPtr point) const;
    void addCell(MeshCellSPtr cell);
    bool removeCell(MeshCellSPtr cell);
    void addRay(MeshRaySPtr ray);
    bool removeRay(MeshRaySPtr ray);

    SharedMutex& mutex();

    map<Point2SPtr, MeshVertexSPtr>& vertices();
    list<MeshCellSPtr>& cells();
    list<MeshRaySPtr>& rays();

    bool isConsistent() const;

    string toString() const;

protected:
    Mesh();
    mutable SharedMutex mutex_;
    map<Point2SPtr, MeshVertexSPtr> vertices_;
    list<MeshCellSPtr> cells_;
    list<MeshRaySPtr> rays_;
};

} } }

#endif	/* DATA_2D_MESH_MESH_H */

