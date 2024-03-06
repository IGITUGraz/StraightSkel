/**
 * @file   data/3d/skel/EdgeEvent.h
 * @author Gernot Walzl
 * @date   2012-04-23
 */

#ifndef DATA_3D_SKEL_EDGEEVENT_H
#define	DATA_3D_SKEL_EDGEEVENT_H

#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/Edge.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/AbstractEvent.h"
#include "data/3d/skel/Node.h"
#include "data/3d/skel/SkelEdgeData.h"

namespace data { namespace _3d { namespace skel {

class EdgeEvent : public AbstractEvent {
public:
    virtual ~EdgeEvent();
    static EdgeEventSPtr create();
    NodeSPtr getNode() const;
    void setNode(NodeSPtr node);
    double getOffset() const;
    EdgeSPtr getEdge() const;
    void setEdge(EdgeSPtr edge);
    void setHighlight(bool highlight);
protected:
    EdgeEvent();
    NodeSPtr node_;
    EdgeSPtr edge_;
};

} } }

#endif	/* DATA_3D_SKEL_EDGEEVENT_H */

