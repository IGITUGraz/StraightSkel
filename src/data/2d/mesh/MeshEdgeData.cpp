/**
 * @file   data/2d/mesh/MeshEdgeData.cpp
 * @author Gernot Walzl
 * @date   2014-03-28
 */

#include "MeshEdgeData.h"

namespace data { namespace _2d { namespace mesh {

MeshEdgeData::MeshEdgeData() {
}

MeshEdgeData::~MeshEdgeData() {
    arcs_.clear();
    rays_.clear();
    cells_.clear();
    edges_.clear();
}

MeshEdgeDataSPtr MeshEdgeData::create(EdgeSPtr edge) {
    MeshEdgeDataSPtr result = MeshEdgeDataSPtr(new MeshEdgeData());
    result->setEdge(edge);
    edge->setData(result);
    return result;
}

void MeshEdgeData::addArc(ArcSPtr arc) {
    arcs_.insert(arcs_.end(), ArcWPtr(arc));
}

bool MeshEdgeData::removeArc(ArcSPtr arc) {
    bool result = false;
    list<ArcWPtr>::iterator it = arcs_.begin();
    while (it != arcs_.end()) {
        list<ArcWPtr>::iterator it_current = it;
        ArcWPtr arc_wptr = *it++;
        if (!arc_wptr.expired()) {
            if (arc_wptr.lock() == arc) {
                arcs_.erase(it_current);
                result = true;
                break;
            }
        }
    }
    return result;
}

void MeshEdgeData::addRay(MeshRaySPtr ray) {
    rays_.insert(rays_.end(), MeshRayWPtr(ray));
}

bool MeshEdgeData::removeRay(MeshRaySPtr ray) {
    bool result = false;
    list<MeshRayWPtr>::iterator it = rays_.begin();
    while (it != rays_.end()) {
        list<MeshRayWPtr>::iterator it_current = it;
        MeshRayWPtr ray_wptr = *it++;
        if (!ray_wptr.expired()) {
            if (ray_wptr.lock() == ray) {
                rays_.erase(it_current);
                result = true;
                break;
            }
        }
    }
    return result;
}

void MeshEdgeData::addCell(MeshCellSPtr cell) {
    cells_.insert(cells_.end(), MeshCellWPtr(cell));
}

bool MeshEdgeData::removeCell(MeshCellSPtr cell) {
    bool result = false;
    list<MeshCellWPtr>::iterator it = cells_.begin();
    while (it != cells_.end()) {
        list<MeshCellWPtr>::iterator it_current = it;
        MeshCellWPtr cell_wptr = *it++;
        if (!cell_wptr.expired()) {
            if (cell_wptr.lock() == cell) {
                cells_.erase(it_current);
                result = true;
                break;
            }
        }
    }
    return result;
}

void MeshEdgeData::addEdge(EdgeSPtr edge) {
    edges_.insert(edges_.end(), EdgeWPtr(edge));
}

bool MeshEdgeData::removeEdge(EdgeSPtr edge) {
    bool result = false;
    list<EdgeWPtr>::iterator it = edges_.begin();
    while (it != edges_.end()) {
        list<EdgeWPtr>::iterator it_current = it;
        EdgeWPtr edge_wptr = *it++;
        if (!edge_wptr.expired()) {
            if (edge_wptr.lock() == edge) {
                edges_.erase(it_current);
                result = true;
                break;
            }
        }
    }
    return result;
}

list<ArcWPtr>& MeshEdgeData::arcs() {
    return this->arcs_;
}

list<MeshRayWPtr>& MeshEdgeData::rays() {
    return this->rays_;
}

list<MeshCellWPtr>& MeshEdgeData::cells() {
    return this->cells_;
}

list<EdgeWPtr>& MeshEdgeData::edges() {
    return this->edges_;
}

} } }
