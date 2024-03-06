/**
 * @file   data/3d/Triangle.h
 * @author Gernot Walzl
 * @date   2011-11-26
 */

#ifndef DATA_3D_TRIANGLE_H
#define	DATA_3D_TRIANGLE_H

#include <list>
#include <string>
#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/Facet.h"

namespace data { namespace _3d {

using std::list;
using std::string;

class Triangle {
public:
    virtual ~Triangle();

    static TriangleSPtr create(FacetSPtr facet, VertexSPtr vertices[3]);

    FacetSPtr getFacet() const;
    void setFacet(FacetSPtr facet);
    list<TriangleSPtr>::iterator getFacetListIt() const;
    void setFacetListIt(list<TriangleSPtr>::iterator list_it);

    VertexSPtr getVertex(unsigned int index) const;
    void setVertices(VertexSPtr vertices[3]);

    Plane3SPtr plane() const;

    int getID() const;
    void setID(int id);

    string toString() const;

protected:
    FacetWPtr facet_;
    list<TriangleSPtr>::iterator facet_list_it_;
    VertexSPtr vertices_[3];
    int id_;
};

} }

#endif	/* DATA_3D_TRIANGLE_H */

