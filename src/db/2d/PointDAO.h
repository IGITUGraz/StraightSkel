/**
 * @file   db/2d/PointDAO.h
 * @author Gernot Walzl
 * @date   2013-05-23
 */

#ifndef DB_2D_POINTDAO_H
#define	DB_2D_POINTDAO_H

#include <string>
#include <map>
#include "data/2d/ptrs.h"
#include "data/2d/KernelFactory.h"
#include "db/ptrs.h"
#include "db/2d/ptrs.h"
#include "db/2d/DAOFactory.h"

namespace db { namespace _2d {

using std::string;
using std::map;
using data::_2d::KernelFactory;
using data::_2d::Point2SPtr;
using data::_2d::Vector2SPtr;

class PointDAO {
friend class DAOFactory;
public:
    virtual ~PointDAO();
    string getTableSchema() const;
    int insert(Point2SPtr point);
    bool del(Point2SPtr point);
    Point2SPtr find(int point_id);
    bool update(Point2SPtr point);
protected:
    PointDAO();
    int nextPointID();
    static map<Point2SPtr, int> point_ids_;
    static map<int, Point2SPtr> points_;
};

} }

#endif	/* DB_2D_POINTDAO_H */

