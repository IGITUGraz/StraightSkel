/**
 * @file   algo/3d/CombiVertexSplitter.h
 * @author Gernot Walzl
 * @date   2012-07-26
 */

#ifndef ALGO_3D_COMBIVERTEXSPLITTER_H
#define	ALGO_3D_COMBIVERTEXSPLITTER_H

#include <list>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <boost/shared_array.hpp>
#include "debug.h"
#include "boost_thread.h"
#include "util/Configuration.h"
#include "data/3d/ptrs.h"
#include "data/3d/Vertex.h"
#include "data/3d/Edge.h"
#include "data/3d/Facet.h"
#include "data/3d/Polyhedron.h"
#include "data/3d/skel/ptrs.h"
#include "data/3d/skel/SkelVertexData.h"
#include "algo/3d/ptrs.h"
#include "algo/3d/AbstractVertexSplitter.h"

namespace algo { namespace _3d {

using std::list;
using std::vector;
using std::map;
using std::string;
using std::stringstream;
using boost::dynamic_pointer_cast;
using namespace data::_3d;
using namespace data::_3d::skel;

typedef boost::shared_array<int> vec2i;
typedef vector<vec2i> combi;

class CombiVertexSplitter : public AbstractVertexSplitter {
public:
    virtual ~CombiVertexSplitter();

    static CombiVertexSplitterSPtr create();

    static vec2i createSplit(int begin, int end);
    static int compareSplits(vec2i split1, vec2i split2);
    static vector<int> initLabels(unsigned int degree);
    static vector<int> splitLabels(vector<int>& labels, vec2i split);
    static list<vec2i> createSingleSplitCombinations(vector<int> labels);
    static list<combi> appendSplitCombinations(
            combi history, list<vec2i> splits);
    static list<combi> mergeCombinations(combi history,
            list<combi> combis1, list<combi> combis2);
    static list<combi> generateCombinationsRec(
            combi history, vector<int> labels);
    static list<combi> generateAllCombinations(unsigned int degree);

    static PolyhedronSPtr copyVertex(VertexSPtr vertex);
    static PolyhedronSPtr splitVertex(VertexSPtr vertex, combi combination);
    static PolyhedronSPtr apply(PolyhedronSPtr poly_split, VertexSPtr vertex);

    virtual PolyhedronSPtr splitVertex(VertexSPtr vertex);

    static string combiToString(combi combination);

    virtual string toString() const;

protected:
    CombiVertexSplitter();

    unsigned int selected_combi_;
};

} }

#endif	/* ALGO_3D_COMBIVERTEXSPLITTER_H */

