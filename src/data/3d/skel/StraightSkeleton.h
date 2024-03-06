/**
 * @file   data/3d/skel/StraightSkeleton.h
 * @author Gernot Walzl
 * @date   2011-11-26
 */

#ifndef DATA_3D_SKEL_STRAIGHTSKELETON_H
#define	DATA_3D_SKEL_STRAIGHTSKELETON_H

#include <list>
#include <string>
#include "boost_thread.h"
#include "util/StringFactory.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/AbstractEvent.h"
#include "data/3d/skel/Node.h"
#include "data/3d/skel/Arc.h"
#include "data/3d/skel/Sheet.h"

namespace data { namespace _3d { namespace skel {

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
    void addSheet(SheetSPtr sheet);
    bool removeSheet(SheetSPtr sheet);

    SharedMutex& mutex();
    list<AbstractEventSPtr>& events();
    list<NodeSPtr>& nodes();
    list<ArcSPtr>& arcs();
    list<SheetSPtr>& sheets();

    PolyhedronSPtr getPolyhedron() const;
    void setPolyhedron(PolyhedronSPtr polyhedron);

    int getID() const;
    void setID(int id);

    void resetAllIDs();

    string getConfig() const;
    void setConfig(string config);
    void appendConfig(string config);

    bool isConsistent() const;

    int countEvents(int type) const;

    string getDescription() const;
    void setDescription(string desc);
    void appendDescription(string desc);

    string toString() const;

protected:
    StraightSkeleton();
    PolyhedronSPtr polyhedron_;
    mutable SharedMutex mutex_;
    list<AbstractEventSPtr> events_;
    list<NodeSPtr> nodes_;
    list<ArcSPtr> arcs_;
    list<SheetSPtr> sheets_;
    int id_;
    string config_;
    string description_;
};

} } }

#endif	/* DATA_3D_SKEL_STRAIGHTSKELETON_H */

