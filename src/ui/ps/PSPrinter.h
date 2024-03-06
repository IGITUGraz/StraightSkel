/**
 * @file   ui/ps/PSPrinter.h
 * @author Gernot Walzl
 * @date   2012-11-06
 */

#ifndef UI_PS_PSPRINTER_H
#define	UI_PS_PSPRINTER_H

#include <iostream>
#include <string>
#include "debug.h"
#include "ui/typedefs.h"
#include "ui/ps/ptrs.h"

namespace ui { namespace ps {

using std::ostream;
using std::string;

class PSPrinter {
public:
    virtual ~PSPrinter();

    void printHead(ostream& out);
    void printComment(string comment, ostream& out);
    void setLineWidth(float linewidth, ostream& out);
    void setGray(float gray, ostream& out);
    void printLine(const vec2f src, const vec2f dst, ostream& out);
    void printPath(unsigned int num_points, const vec2f points[],
            bool closepath, bool fill, ostream& out);
    void printCircle(const vec2f center, float radius, ostream& out);

protected:
    PSPrinter();

    int bounding_box_[4];
};

} }

#endif	/* UI_PS_PSPRINTER_H */

