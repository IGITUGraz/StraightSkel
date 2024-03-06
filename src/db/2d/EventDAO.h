/**
 * @file   db/2d/EventDAO.h
 * @author Gernot Walzl
 * @date   2013-06-04
 */

#ifndef DB_2D_EVENTDAO_H
#define	DB_2D_EVENTDAO_H

#include <string>
#include "data/2d/ptrs.h"
#include "data/2d/skel/ptrs.h"
#include "data/2d/skel/AbstractEvent.h"
#include "data/2d/skel/ConstOffsetEvent.h"
#include "data/2d/skel/EdgeEvent.h"
#include "data/2d/skel/SplitEvent.h"
#include "data/2d/skel/TriangleEvent.h"
#include "data/2d/skel/StraightSkeleton.h"
#include "db/ptrs.h"
#include "db/2d/ptrs.h"
#include "db/2d/DAOFactory.h"

namespace db { namespace _2d {

using std::string;
using boost::dynamic_pointer_cast;
using data::_2d::skel::AbstractEvent;
using data::_2d::skel::AbstractEventSPtr;

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

#endif	/* DB_2D_EVENTDAO_H */

