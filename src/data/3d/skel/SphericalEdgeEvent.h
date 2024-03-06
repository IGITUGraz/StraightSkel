/**
 * @file   data/3d/skel/SphericalEdgeEvent.h
 * @author Gernot Walzl
 * @date   2012-11-29
 */

#ifndef DATA_3D_SKEL_SPHERICALEDGEEVENT_H
#define	DATA_3D_SKEL_SPHERICALEDGEEVENT_H

#include "debug.h"
#include "data/3d/ptrs.h"
#include "data/3d/CircularEdge.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/SphericalAbstractEvent.h"
#include "data/3d/skel/CircularNode.h"
#include "data/3d/skel/SphericalSkelEdgeData.h"

namespace data { namespace _3d { namespace skel {

class SphericalEdgeEvent : public SphericalAbstractEvent {
public:
    virtual ~SphericalEdgeEvent();
    static SphericalEdgeEventSPtr create();
    CircularNodeSPtr getNode() const;
    void setNode(CircularNodeSPtr node);
    double getOffset() const;
    CircularEdgeSPtr getEdge() const;
    void setEdge(CircularEdgeSPtr edge);
    void setHighlight(bool highlight);
protected:
    SphericalEdgeEvent();
    CircularNodeSPtr node_;
    CircularEdgeSPtr edge_;
};

} } }

#endif	/* DATA_3D_SKEL_SPHERICALEDGEEVENT_H */

