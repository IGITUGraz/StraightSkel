/**
 * @file   db/3d/EventDAO.h
 * @author Gernot Walzl
 * @date   2013-06-04
 */

#ifndef DB_3D_EVENTDAO_H
#define	DB_3D_EVENTDAO_H

#include <string>
#include "data/3d/ptrs.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/AbstractEvent.h"
#include "data/3d/skel/ConstOffsetEvent.h"
#include "data/3d/skel/EdgeEvent.h"
#include "data/3d/skel/EdgeMergeEvent.h"
#include "data/3d/skel/TriangleEvent.h"
#include "data/3d/skel/DblEdgeMergeEvent.h"
#include "data/3d/skel/DblTriangleEvent.h"
#include "data/3d/skel/TetrahedronEvent.h"
#include "data/3d/skel/VertexEvent.h"
#include "data/3d/skel/FlipVertexEvent.h"
#include "data/3d/skel/SurfaceEvent.h"
#include "data/3d/skel/PolyhedronSplitEvent.h"
#include "data/3d/skel/SplitMergeEvent.h"
#include "data/3d/skel/EdgeSplitEvent.h"
#include "data/3d/skel/PierceEvent.h"
#include "data/3d/skel/StraightSkeleton.h"
#include "db/ptrs.h"
#include "db/3d/ptrs.h"
#include "db/3d/DAOFactory.h"

namespace db { namespace _3d {

using std::string;
using boost::dynamic_pointer_cast;
using data::_3d::skel::AbstractEvent;
using data::_3d::skel::AbstractEventSPtr;

class EventDAO {
friend class DAOFactory;
public:
    virtual ~EventDAO();
    string getTableSchema() const;
    int insert(AbstractEventSPtr event);
    bool del(AbstractEventSPtr event);
    AbstractEventSPtr find(int skelid, int eventid);
    bool update(AbstractEventSPtr event);
protected:
    EventDAO();
    int nextEventID(int skelid);
};

} }

#endif	/* DB_3D_EVENTDAO_H */

