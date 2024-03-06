/**
 * @file   data/2d/mesh/MeshCell.h
 * @author Gernot Walzl
 * @date   2014-01-24
 */

#ifndef DATA_2D_MESH_MESHCELL_H
#define	DATA_2D_MESH_MESHCELL_H

#include <list>
#include <string>
#include "debug.h"
#include "util/StringFactory.h"
#include "data/2d/ptrs.h"
#include "data/2d/mesh/ptrs.h"
#include "data/2d/mesh/MeshVertex.h"

namespace data { namespace _2d { namespace mesh {

using std::list;
using std::string;
using util::StringFactory;

class MeshCell : public boost::enable_shared_from_this<MeshCell> {
public:
    virtual ~MeshCell();
    static MeshCellSPtr create();

    static MeshCellSPtr create(unsigned int num_vertices, MeshVertexSPtr vertices[]);

    MeshSPtr getMesh() const;
    void setMesh(MeshSPtr mesh);
    list<MeshCellSPtr>::iterator getListIt() const;
    void setListIt(list<MeshCellSPtr>::iterator list_it);

    void addVertex(MeshVertexSPtr vertex);
    bool removeVertex(MeshVertexSPtr vertex);
    bool addVertexBefore(MeshVertexSPtr position, MeshVertexSPtr vertex);
    bool containsVertex(MeshVertexSPtr vertex) const;

    MeshCellSPtr next(MeshVertexSPtr vertex);
    MeshCellSPtr prev(MeshVertexSPtr vertex);

    list<MeshVertexSPtr>& vertices();

    string toString() const;

protected:
    MeshCell();
    MeshWPtr mesh_;
    list<MeshCellSPtr>::iterator list_it_;
    list<MeshVertexSPtr> vertices_;
};

} } }

#endif	/* DATA_2D_MESH_MESHCELL_H */

