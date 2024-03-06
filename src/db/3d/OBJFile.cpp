/**
 * @file   db/3d/OBJFile.cpp
 * @author Gernot Walzl
 * @date   2012-05-15
 */

#include "OBJFile.h"

namespace db { namespace _3d {

OBJFile::OBJFile() {
    // intentionally does nothing
}

OBJFile::~OBJFile() {
    // intentionally does nothing
}

PolyhedronSPtr OBJFile::load(string filename) {
    PolyhedronSPtr result = PolyhedronSPtr();
    ifstream ifs(filename.c_str());
    if (ifs.is_open()) {
        result = Polyhedron::create();
        unsigned int vertex_id_new = 0;
        unsigned int facet_id_new = 0;
        vector<VertexSPtr> vertices;
        vector<Vector3SPtr> normals;
        while (ifs.good()) {
            string line;
            getline(ifs, line);
            if (line.find("v ") == 0) {  // vertex
                vector<string> strs = util::StringFuncs::split(line, " \t", false);
                if (strs.size() >= 4) {
                    vertex_id_new++;
                    Point3SPtr point = KernelFactory::createPoint3(
                            atof(strs[1].c_str()), atof(strs[2].c_str()), atof(strs[3].c_str()));
                    VertexSPtr vertex = Vertex::create(point);
                    vertex->setID(vertex_id_new);
                    result->addVertex(vertex);
                }
            } else if (line.find("vn ") == 0) {  // vertex normal
                vector<string> strs = util::StringFuncs::split(line, " \t", false);
                if (strs.size() >= 4) {
                    Vector3SPtr normal = KernelFactory::createVector3(
                            atof(strs[1].c_str()), atof(strs[2].c_str()), atof(strs[3].c_str()));
                    normals.push_back(normal);
                }
            } else if (line.find("f ") == 0) {  // face
                if (vertices.size() != result->vertices().size()) {  // initialize vector
                    vertices = vector<VertexSPtr>(
                            result->vertices().begin(), result->vertices().end());
                }
                vector<string> strs = util::StringFuncs::split(line, " \t", false);
                if (strs.size() >= 4) {
                    facet_id_new++;
                    unsigned int num_vertices = strs.size() - 1;
                    VertexSPtr poly_vertices[num_vertices];
                    Vector3SPtr normal_sum;
                    for (unsigned int i = 0; i < num_vertices; i++) {
                        poly_vertices[i] = VertexSPtr();
                    }
                    for (unsigned int i = 0; i < num_vertices; i++) {
                        vector<string> strsvertex =
                                util::StringFuncs::split(strs[i+1], "/", true);
                        if (strsvertex.size() > 0) {
                            unsigned int vertex_id = atoi(strsvertex[0].c_str());
                            if (0 < vertex_id && vertex_id <= vertices.size()) {
                                poly_vertices[i] = vertices[vertex_id - 1];
                            } else {
                                std::stringstream whatstream;
                                whatstream << "Vertex with id="
                                        << vertex_id
                                        << " does not exist.";
                                throw std::runtime_error(whatstream.str());
                            }
                            if (strsvertex.size() > 2) {
                                unsigned int normal_id = atoi(strsvertex[2].c_str());
                                if (0 < normal_id && normal_id <= normals.size()) {
                                    Vector3SPtr normal = normals[normal_id - 1];
                                    if (normal_sum) {
                                        normal_sum = KernelFactory::createVector3(*normal_sum + *normal);
                                    } else {
                                        normal_sum = normal;
                                    }
                                }
                            }
                        }
                    }
                    FacetSPtr facet = Facet::create(num_vertices, poly_vertices);
                    facet->setID(facet_id_new);
                    if (num_vertices == 3) {
                        Triangle::create(facet, poly_vertices);
                    } else if (normal_sum && num_vertices > 3) {
                        // vertex normals are used as a hint for facet normal
                        Plane3SPtr plane = KernelFactory::createPlane3(
                                poly_vertices[0]->getPoint(),
                                poly_vertices[1]->getPoint(),
                                poly_vertices[2]->getPoint());
                        Vector3SPtr normal_plane = KernelFactory::createVector3(plane);
                        double angle = 0.0;
                        double arg = 0.0;
#ifdef USE_CGAL
                        arg = ((*normal_plane)*(*normal_sum)) /
                                CGAL::sqrt(normal_plane->squared_length() * normal_sum->squared_length());
#else
                        arg = ((*normal_plane)*(*normal_sum)) /
                                sqrt(normal_plane->squared_length() * normal_sum->squared_length());
#endif
                        // fixes issues with floating point precision
                        if (arg <= -1.0) {
                            angle = M_PI;
                        } else if (arg >= 1.0) {
                            angle = 0.0;
                        } else {
                            angle = acos(arg);
                        }
                        if (angle > M_PI/2.0) {
                            plane = KernelFactory::createPlane3(
                                    poly_vertices[2]->getPoint(),
                                    poly_vertices[1]->getPoint(),
                                    poly_vertices[0]->getPoint());
                        }
                        facet->setPlane(plane);
                        facet->makeFirstConvex();
                    }
                    facet->initPlane();
                    result->addFacet(facet);
                }
            }
        }
        ifs.close();
        result->setDescription("filename='"+filename+"'; ");
        list<EdgeSPtr>::iterator it_e = result->edges().begin();
        while (it_e != result->edges().end()) {
            EdgeSPtr edge = *it_e++;
            if (!(edge->getFacetL() && edge->getFacetR())) {
                DEBUG_VAL("Warning: Polyhedron has no closed boundary.");
                DEBUG_VAR(edge->toString());
            }
        }
        double epsilon = 0.0001;
        util::ConfigurationSPtr config = util::Configuration::getInstance();
        string section("db_3d_OBJFile");
        string key("epsilon_coplanarity");
        if (config->contains(section, key)) {
            epsilon = config->getDouble(section, key);
        }
        mergeCoplanarFacets(result, epsilon);
        removeVerticesDegLt3(result);
        assert(result->isConsistent());
    }
    return result;
}

bool OBJFile::save(string filename, PolyhedronSPtr polyhedron) {
    bool result = false;
    ofstream ofs(filename.c_str());
    if (ofs.is_open()) {
        WriteLock l(polyhedron->mutex());
        unsigned int vertex_id = 0;
        list<VertexSPtr>::iterator it_v = polyhedron->vertices().begin();
        while (it_v != polyhedron->vertices().end()) {
            VertexSPtr vertex = *it_v++;
            vertex_id++;
            vertex->setID(vertex_id);
            ofs << "v " << vertex->getX() << " "
                        << vertex->getY() << " "
                        << vertex->getZ() << "\n";
        }
        unsigned int facet_id = 0;
        list<FacetSPtr>::iterator it_f = polyhedron->facets().begin();
        while (it_f != polyhedron->facets().end()) {
            FacetSPtr facet = *it_f++;
            facet->makeFirstConvex();
            facet_id++;
            facet->setID(facet_id);
            ofs << "f ";
            unsigned int num_edges = 0;
            EdgeSPtr first = EdgeSPtr();
            EdgeSPtr edge = facet->edges().front();
            while (first != edge) {
                if (!first) {
                    first = edge;
                } else {
                    ofs << " ";
                }
                VertexSPtr vertex = edge->src(facet);
                ofs << vertex->getID();
                edge = edge->next(facet);
                num_edges++;
            }
            if (num_edges != facet->edges().size()) {
                DEBUG_VAL("Warning: Facet does not consist of connected edges only.");
                DEBUG_VAL("Warning: It is impossible for an obj file to store holes inside a facet.");
                DEBUG_VAR(facet->toString());
            }
            ofs << "\n";
        }
        result = (polyhedron->vertices().size() == vertex_id &&
                  polyhedron->facets().size() == facet_id);
        ofs.close();
    }
    return result;
}

} }
