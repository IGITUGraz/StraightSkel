/**
 * @file   algo/3d/VolumeVertexSplitter.h
 * @author Gernot Walzl
 * @date   2013-01-27
 */

#ifndef ALGO_3D_VOLUMEVERTEXSPLITTER_H
#define	ALGO_3D_VOLUMEVERTEXSPLITTER_H

#include "data/3d/ptrs.h"
#include "data/3d/skel/ptrs.h"
#include "data/2d/ptrs.h"
#include "data/2d/Vertex.h"
#include "data/2d/Polygon.h"
#include "algo/ptrs.h"
#include "algo/3d/ptrs.h"
#include "algo/3d/AbstractVertexSplitter.h"
#include "algo/3d/CombiVertexSplitter.h"

namespace algo { namespace _3d {

using std::string;

class VolumeVertexSplitter : public CombiVertexSplitter {
public:
    virtual ~VolumeVertexSplitter();

    static VolumeVertexSplitterSPtr create();

    /**
     * A = \frac{1}{2}\sum_{i=0}^{N-1} (x_i\ y_{i+1} - x_{i+1}\ y_i)
     * http://de.wikipedia.org/wiki/Geometrischer_Schwerpunkt
     */
    static double calcArea(FacetSPtr facet);
    static double calcSurfaceArea(PolyhedronSPtr polyhedron);

    static void closeFacets(PolyhedronSPtr polyhedron);
    static int compareSurfaceAreas(PolyhedronSPtr polyhedron_1, PolyhedronSPtr polyhedron_2);

    virtual PolyhedronSPtr splitVertex(VertexSPtr vertex);

    virtual string toString() const;

protected:
    VolumeVertexSplitter();
    int optimization_;
};

} }

#endif	/* ALGO_3D_VOLUMEVERTEXSPLITTER_H */

