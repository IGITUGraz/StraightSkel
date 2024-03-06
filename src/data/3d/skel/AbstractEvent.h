/**
 * @file   data/3d/skel/AbstractEvent.h
 * @author Gernot Walzl
 * @date   2012-03-27
 */

#ifndef DATA_3D_SKEL_ABSTRACTEVENT_H
#define	DATA_3D_SKEL_ABSTRACTEVENT_H

#include <list>
#include <string>
#include <sstream>
#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/skel/ptrs.h"
#include "util/StringFactory.h"

namespace data { namespace _3d { namespace skel {

using std::list;
using std::string;
using std::stringstream;
using util::StringFactory;

class AbstractEvent {
public:
    virtual ~AbstractEvent();

    PolyhedronSPtr getPolyhedronResult() const;
    void setPolyhedronResult(PolyhedronSPtr polyhedron);
    StraightSkeletonSPtr getSkel() const;
    void setSkel(StraightSkeletonSPtr skel);
    list<AbstractEventSPtr>::iterator getListIt() const;
    void setListIt(list<AbstractEventSPtr>::iterator list_it);

    int getID() const;
    void setID(int id);

    virtual void setHighlight(bool highlight);
    virtual double getOffset() const = 0;  // abstract

    static const int CONST_OFFSET_EVENT = 1;

    /** 1 edge vanish event */
    static const int EDGE_EVENT = 2;

    /** 2 edge vanish event */
    static const int EDGE_MERGE_EVENT = 3;

    /** 3 edge vanish event */
    static const int TRIANGLE_EVENT = 4;

    /** 4 edge vanish event */
    static const int DBL_EDGE_MERGE_EVENT = 5;

    /** 5 edge vanish event */
    static const int DBL_TRIANGLE_EVENT = 6;

    /** 6 edge vanish event */
    static const int TETRAHEDRON_EVENT = 7;

    /** vertex-vertex contact event I */
    static const int VERTEX_EVENT = 8;

    /** vertex-vertex contact event II */
    static const int FLIP_VERTEX_EVENT = 9;

    /** vertex-edge contact event */
    static const int SURFACE_EVENT = 10;

    /** vertex-vertex-edge contact event I */
    static const int POLYHEDRON_SPLIT_EVENT = 11;

    /** vertex-vertex-edge contact event II */
    static const int SPLIT_MERGE_EVENT = 12;

    /** edge-edge contact event */
    static const int EDGE_SPLIT_EVENT = 13;

    /** vertex-facet contact event */
    static const int PIERCE_EVENT = 14;

    virtual int getType() const;

    virtual string toString() const;

protected:
    AbstractEvent();

    PolyhedronSPtr polyhedron_result_;
    StraightSkeletonWPtr skel_;
    list<AbstractEventSPtr>::iterator list_it_;
    int type_;
    int id_;
};

} } }

#endif	/* DATA_3D_ABSTRACTEVENT_H */

