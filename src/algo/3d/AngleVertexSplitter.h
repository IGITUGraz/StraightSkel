/**
 * @file   algo/3d/AngleVertexSplitter.h
 * @author Gernot Walzl
 * @date   2012-10-01
 */

#ifndef ALGO_3D_ANGLEVERTEXSPLITTER_H
#define	ALGO_3D_ANGLEVERTEXSPLITTER_H

#include "data/3d/ptrs.h"
#include "data/3d/Vertex.h"
#include "data/3d/Polyhedron.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/SkelVertexData.h"
#include "algo/3d/ptrs.h"
#include "algo/3d/KernelWrapper.h"
#include "algo/3d/AbstractVertexSplitter.h"

namespace algo { namespace _3d {

using boost::dynamic_pointer_cast;
using namespace data::_3d;
using namespace data::_3d::skel;

class AngleVertexSplitter : public AbstractVertexSplitter {
public:
    virtual ~AngleVertexSplitter();

    static AngleVertexSplitterSPtr create();

    /**
     * All vertices of the input polyhedron have to have a maximum degree of 3.
     * Using the angle between 2 planes does not work in every case.
     */
    virtual PolyhedronSPtr splitVertex(VertexSPtr vertex);

protected:
    AngleVertexSplitter();
};

} }

#endif	/* ALGO_3D_ANGLEVERTEXSPLITTER_H */

