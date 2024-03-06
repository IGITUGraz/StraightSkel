/**
 * @file   data/2d/skel/StraightSkeleton.h
 * @author Gernot Walzl
 * @date   2011-11-21
 */

#ifndef DATA_2D_SKEL_STRAIGHTSKELETON_H
#define	DATA_2D_SKEL_STRAIGHTSKELETON_H

#include <list>
#include <string>
#include "boost_thread.h"
#include "util/StringFactory.h"
#include "data/2d/ptrs.h"
#include "data/2d/skel/ptrs.h"
#include "data/2d/skel/Node.h"
#include "data/2d/skel/Arc.h"
#include "data/2d/skel/AbstractEvent.h"
#include "data/2d/skel/EdgeEvent.h"
#include "data/2d/skel/SplitEvent.h"
#include "data/2d/skel/TriangleEvent.h"

namespace data { namespace _2d { namespace skel {

using std::list;
using std::string;
using std::stringstream;
using boost::dynamic_pointer_cast;
using util::StringFactory;

class StraightSkeleton : public boost::enable_shared_from_this<StraightSkeleton> {
public:
    virtual ~StraightSkeleton();

    static StraightSkeletonSPtr create();

    /**
     * also adds the node
     */
    void addEvent(AbstractEventSPtr event);
    bool removeEvent(AbstractEventSPtr event);
    void addNode(NodeSPtr node);
    bool removeNode(NodeSPtr node);
    void addArc(ArcSPtr arc);
    bool removeArc(ArcSPtr arc);

    SharedMutex& mutex();
    list<AbstractEventSPtr>& events();
    list<NodeSPtr>& nodes();
    list<ArcSPtr>& arcs();

    PolygonSPtr getPolygon() const;
    void setPolygon(PolygonSPtr polygon);

    int getID() const;
    void setID(int id);

    void resetAllIDs();

    bool isConsistent() const;

    int countEvents(int type) const;

    string getDescription() const;
    void setDescription(string desc);
    void appendDescription(string desc);

    string toString() const;

protected:
    StraightSkeleton();
    PolygonSPtr polygon_;
    mutable SharedMutex mutex_;
    list<AbstractEventSPtr> events_;
    list<NodeSPtr> nodes_;
    list<ArcSPtr> arcs_;
    int id_;
    string description_;
};

} } }

#endif	/* DATA_2D_SKEL_STRAIGHTSKELETON_H */

