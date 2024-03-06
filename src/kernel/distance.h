/**
 * @file   kernel/distance.h
 * @author Gernot Walzl
 * @date   2012-02-25
 */

#ifndef DISTANCE_H
#define	DISTANCE_H

#include <cmath>
#include "Point2.h"
#include "Line2.h"
#include "Point3.h"
#include "Plane3.h"
#include "Line3.h"

namespace kernel {

double distance(const Point2* p, const Point2* q);
double distance(const Line2* line, const Point2* point);

double distance(const Point3* p, const Point3* q);
double distance(const Plane3* plane, const Point3* point);
double distance(const Line3* line, const Point3* point);

}

#endif	/* DISTANCE_H */

