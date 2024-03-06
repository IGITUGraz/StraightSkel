/**
 * @file   data/3d/skel/Sheet.h
 * @author Gernot Walzl
 * @date   2012-03-27
 */

#ifndef DATA_3D_SKEL_SHEET_H
#define	DATA_3D_SKEL_SHEET_H

#include <list>
#include <string>
#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/KernelFactory.h"
#include "data/3d/Facet.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/Node.h"
#include "data/3d/skel/Arc.h"

namespace data { namespace _3d { namespace skel {

using std::list;
using std::string;
using std::stringstream;

class Sheet : public boost::enable_shared_from_this<Sheet> {
public:
    virtual ~Sheet();
    static SheetSPtr create();

    FacetSPtr getFacetB() const;
    void setFacetB(FacetSPtr facet_b);
    FacetSPtr getFacetF() const;
    void setFacetF(FacetSPtr facet_f);

    StraightSkeletonSPtr getSkel() const;
    void setSkel(StraightSkeletonSPtr skel);
    list<SheetSPtr>::iterator getListIt() const;
    void setListIt(list<SheetSPtr>::iterator list_it);

    int getID() const;
    void setID(int id);

    Plane3SPtr getPlane() const;
    void setPlane(Plane3SPtr plane);

    void addNode(NodeSPtr node);
    bool removeNode(NodeSPtr node);

    void addArc(ArcSPtr arc);
    bool removeArc(ArcSPtr arc);

    list<ArcSPtr>& arcs();
    list<NodeSPtr>& nodes();

    string toString() const;

protected:
    Sheet();
    FacetSPtr facet_b_;
    FacetSPtr facet_f_;
    list<ArcSPtr> arcs_;
    list<NodeSPtr> nodes_;
    StraightSkeletonWPtr skel_;
    list<SheetSPtr>::iterator list_it_;
    Plane3SPtr plane_;
    int id_;
};

} } }

#endif	/* DATA_3D_SKEL_SHEET_H */

