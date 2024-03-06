/**
 * @file   algo/2d/SkelMeshGenerator.h
 * @author Gernot Walzl
 * @date   2014-01-28
 */

#ifndef ALGO_2D_SKELMESHGENERATOR_H
#define	ALGO_2D_SKELMESHGENERATOR_H

#include <list>
#include "debug.h"
#include "boost_thread.h"
#include "data/2d/ptrs.h"
#include "data/2d/Polygon.h"
#include "data/2d/skel/ptrs.h"
#include "data/2d/skel/StraightSkeleton.h"
#include "data/2d/mesh/ptrs.h"
#include "data/2d/mesh/Mesh.h"
#include "data/2d/mesh/MeshEdgeData.h"
#include "algo/ptrs.h"
#include "algo/Controller.h"
#include "algo/2d/ptrs.h"
#include "algo/2d/KernelWrapper.h"
#include "algo/2d/MeshModifier.h"

namespace algo { namespace _2d {

using std::list;
using namespace data::_2d;
using namespace data::_2d::skel;
using namespace data::_2d::mesh;

class SkelMeshGenerator {
public:
    virtual ~SkelMeshGenerator();
    static SkelMeshGeneratorSPtr create(StraightSkeletonSPtr skel);
    static SkelMeshGeneratorSPtr create(StraightSkeletonSPtr skel, ControllerSPtr controller);

    void initEdgeDatas();
    void sortArcs(EdgeSPtr edge);
    void initCells();
    void createRays(EdgeSPtr edge);
    void findRayDsts();
    void sortRays(EdgeSPtr edge);
    void splitCellR(EdgeSPtr edge);

    MeshVertexSPtr findNearestIntersection(MeshCellSPtr cell,
            MeshVertexSPtr vertex, Vector2SPtr direction);
    MeshCellSPtr splitCell(MeshCellSPtr cell,
            MeshVertexSPtr v_src, MeshVertexSPtr v_dst);

    void offsetEdges();
    void splitCellsE(EdgeSPtr edge, double radius_snap);

    MeshCellSPtr splitCell(MeshCellSPtr cell, Line2SPtr line,
            double radius_snap);

    void mergeAdjTriangles();
    void mergeVertices();

    void run();
    ThreadSPtr startThread();
    MeshSPtr getResult() const;
protected:
    SkelMeshGenerator(StraightSkeletonSPtr skel);
    SkelMeshGenerator(StraightSkeletonSPtr skel, ControllerSPtr controller);

    StraightSkeletonSPtr skel_;
    ControllerSPtr controller_;
    MeshSPtr mesh_result_;
};

} }

#endif	/* ALGO_2D_SKELMESHGENERATOR_H */

