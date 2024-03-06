/**
 * @file   db/3d/SheetDAO.h
 * @author Gernot Walzl
 * @date   2013-06-05
 */

#ifndef DB_3D_SHEETDAO_H
#define	DB_3D_SHEETDAO_H

#include <list>
#include <string>
#include "data/3d/ptrs.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/Arc.h"
#include "data/3d/skel/Sheet.h"
#include "data/3d/skel/StraightSkeleton.h"
#include "db/ptrs.h"
#include "db/3d/ptrs.h"
#include "db/3d/DAOFactory.h"

namespace db { namespace _3d {

using std::list;
using std::string;
using data::_3d::skel::Sheet;
using data::_3d::skel::SheetSPtr;

class SheetDAO {
friend class DAOFactory;
public:
    virtual ~SheetDAO();
    string getTableSchema() const;
    string getTable2Schema() const;
    int insert(SheetSPtr sheet);
    bool del(SheetSPtr sheet);
    SheetSPtr find(int skelid, int sid);
    bool update(SheetSPtr node);
protected:
    SheetDAO();
    int nextSID(int skelid);
};

} }

#endif	/* DB_3D_SHEETDAO_H */

