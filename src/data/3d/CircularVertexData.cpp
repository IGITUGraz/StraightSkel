/**
 * @file   data/3d/CircularVertexData.cpp
 * @author Gernot Walzl
 * @date   2012-11-30
 */

#include "CircularVertexData.h"

namespace data { namespace _3d {

CircularVertexData::CircularVertexData() {
    highlight_ = false;
}

CircularVertexData::~CircularVertexData() {
    // intentionally does nothing
}

CircularVertexSPtr CircularVertexData::getVertex() const {
    DEBUG_WPTR(vertex_);
    if (this->vertex_.expired())
        return CircularVertexSPtr();
    else
        return CircularVertexSPtr(this->vertex_);
}

void CircularVertexData::setVertex(CircularVertexSPtr vertex) {
    this->vertex_ = vertex;
}

bool CircularVertexData::isHighlight() const {
    return highlight_;
}

void CircularVertexData::setHighlight(bool highlight) {
    highlight_ = highlight;
}

} }
