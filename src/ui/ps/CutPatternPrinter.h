/**
 * @file   ui/ps/CutPatternPrinter.h
 * @author Gernot Walzl
 * @date   2012-11-14
 */

#ifndef UI_PS_CUTPATTERNPRINTER_H
#define	UI_PS_CUTPATTERNPRINTER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <list>
#include "boost_thread.h"
#include "util/Configuration.h"
#include "ui/ps/ptrs.h"
#include "ui/ps/PlanePSPrinter.h"
#include "data/3d/ptrs.h"
#include "data/3d/Polyhedron.h"
#include "data/2d/ptrs.h"
#include "data/2d/Polygon.h"

namespace ui { namespace ps {

using std::string;
using std::list;
using data::_3d::PolyhedronSPtr;

class CutPatternPrinter {
public:
    virtual ~CutPatternPrinter();

    static void printCutPattern(PolyhedronSPtr polyhedron, string filename_prefix);

protected:
    CutPatternPrinter();
};

} }

#endif	/* UI_PS_CUTPATTERNPRINTER_H */

