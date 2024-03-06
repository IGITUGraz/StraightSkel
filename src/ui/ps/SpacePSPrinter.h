/**
 * @file   ui/ps/SpacePSPrinter.h
 * @author Gernot Walzl
 * @date   2012-11-14
 */

#ifndef UI_PS_SPACEPSPRINTER_H
#define	UI_PS_SPACEPSPRINTER_H

#include <iostream>
#include <list>
#include "boost_thread.h"
#include "ui/vecmath.h"
#include "ui/ps/ptrs.h"
#include "ui/ps/PSPrinter.h"
#include "data/3d/ptrs.h"
#include "data/3d/Polyhedron.h"
#include "data/3d/Edge.h"
#include "data/3d/Vertex.h"
#include "data/3d/SphericalPolygon.h"
#include "data/3d/CircularEdge.h"
#include "data/3d/CircularVertex.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/StraightSkeleton.h"
#include "data/3d/skel/Arc.h"
#include "data/3d/skel/Node.h"
#include "data/3d/skel/SphericalSkeleton.h"
#include "data/3d/skel/CircularArc.h"
#include "data/3d/skel/CircularNode.h"

namespace ui { namespace ps {

using std::ostream;
using std::list;
using data::_3d::PolyhedronSPtr;
using data::_3d::SphericalPolygonSPtr;

class SpacePSPrinter : public PSPrinter {
public:
    virtual ~SpacePSPrinter();

    static SpacePSPrinterSPtr create();

    void initBoundingBox();

    void setModelviewMatrix(float modelview[16]);
    void setProjectionMatrix(float projection[16]);
    void setViewport(int viewport[4]);

    void setCamEye(const vec3f cam_eye);
    void setCamCenter(const vec3f cam_center);

    void printCommentCamera(ostream& out);

    /**
     * p_2 = P * V * p_3
     */
    void to2d(const vec3f p3, vec2f& p2);

    void printLine3(const vec3f src, const vec3f dst, ostream& out);

    void printPolyhedron(PolyhedronSPtr polyhedron, ostream& out);
    void printPolyhedronShade(PolyhedronSPtr polyhedron,
            float min_gray, float max_gray, bool print_edges, ostream& out);
    void printSkel(data::_3d::skel::StraightSkeletonSPtr skel, ostream& out);

    float to2dRadius(const vec3f center, float radius);

    void printSphere(const vec3f center, float radius, ostream& out);
    void printCircularEdge(const vec3f center, const vec3f axis,
            const vec3f src, const vec3f dst, ostream& out);

    void printSphericalPolygon(
            SphericalPolygonSPtr sphericalpolygon, ostream& out);
    void printSphericalIntersections(
            SphericalPolygonSPtr sphericalpolygon, ostream& out);
    void printSphericalSkel(
            data::_3d::skel::SphericalSkeletonSPtr sphericalskel, ostream& out);

protected:
    SpacePSPrinter();

    list<data::_3d::FacetSPtr> getFacetsToShade(PolyhedronSPtr polyhedron);

    /**
     * index = row + 4*column
     */
    float modelview_[16];
    float projection_[16];
    int viewport_[4];

    vec3f cam_eye_;
    vec3f cam_center_;
};

} }

#endif	/* UI_PS_SPACEPSPRINTER_H */

