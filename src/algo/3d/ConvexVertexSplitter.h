/**
 * @file   algo/3d/ConvexVertexSplitter.h
 * @author Gernot Walzl
 * @date   2013-02-01
 */

#ifndef ALGO_3D_CONVEXVERTEXSPLITTER_H
#define	ALGO_3D_CONVEXVERTEXSPLITTER_H

#include "data/3d/ptrs.h"
#include "data/3d/Vertex.h"
#include "data/3d/Edge.h"
#include "data/3d/Polyhedron.h"
#include "algo/ptrs.h"
#include "algo/3d/ptrs.h"
#include "algo/3d/AbstractVertexSplitter.h"
#include "algo/3d/CombiVertexSplitter.h"

namespace algo { namespace _3d {

using std::string;

class ConvexVertexSplitter : public CombiVertexSplitter {
public:
    virtual ~ConvexVertexSplitter();

    static ConvexVertexSplitterSPtr create();

    static int countConvexEdges(PolyhedronSPtr polyhedron);

    virtual PolyhedronSPtr splitVertex(VertexSPtr vertex);

    virtual string toString() const;

protected:
    ConvexVertexSplitter();
    int optimization_;
};

} }

#endif	/* ALGO_3D_CONVEXVERTEXSPLITTER_H */

