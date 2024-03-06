/**
 * @file   db/3d/ArcDAO.h
 * @author Gernot Walzl
 * @date   2013-06-03
 */

#ifndef DB_3D_ARCDAO_H
#define	DB_3D_ARCDAO_H

#include <string>
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/Arc.h"
#include "data/3d/skel/StraightSkeleton.h"
#include "db/ptrs.h"
#include "db/3d/ptrs.h"
#include "db/3d/DAOFactory.h"

namespace db { namespace _3d {

using std::string;
using data::_3d::skel::Arc;
using data::_3d::skel::ArcSPtr;

class ArcDAO {
friend class DAOFactory;
public:
    virtual ~ArcDAO();
    string getTableSchema() const;
    int insert(ArcSPtr arc);
    bool del(ArcSPtr arc);
    ArcSPtr find(int skelid, int aid);
    bool update(ArcSPtr arc);
protected:
    ArcDAO();
    int nextAID(int skelid);
};

} }

#endif	/* DB_3D_ARCDAO_H */

