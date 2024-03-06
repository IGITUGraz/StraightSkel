/**
 * @file   main.cpp
 * @author Gernot Walzl
 * @date   2011-12-19
 *
 * @mainpage
 * StraightSkel is an implementation of the Straight Skeleton in 2- and
 * 3-dimensional space. It is used to animate the computation of offsets
 * of polygons and polyhedrons.
 * StraightSkel was written by Gernot Walzl in the years 2011, 2012, 2013.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "boost_thread.h"
#include "util/StringFuncs.h"

#include "data/2d/ptrs.h"
#include "data/2d/Polygon.h"
#include "data/3d/ptrs.h"
#include "data/3d/Polyhedron.h"

#include "db/2d/ptrs.h"
#include "db/2d/DAOFactory.h"
#include "db/2d/PolygonDAO.h"
#include "db/2d/StraightSkeletonDAO.h"
#include "db/2d/FLMAFile.h"
#include "db/3d/ptrs.h"
#include "db/3d/DAOFactory.h"
#include "db/3d/PolyhedronDAO.h"
#include "db/3d/StraightSkeletonDAO.h"
#include "db/3d/OBJFile.h"
#include "db/3d/FLMAFile.h"

#include "algo/ptrs.h"
#include "algo/Controller.h"
#include "algo/2d/ptrs.h"
#include "algo/2d/PolygonTransformation.h"
#include "algo/2d/SimpleStraightSkel.h"
#include "algo/2d/FastStraightSkel.h"
#include "algo/2d/SkelMeshGenerator.h"
#include "algo/3d/ptrs.h"
#include "algo/3d/PolyhedronBuilder.h"
#include "algo/3d/PolyhedronTransformation.h"
#include "algo/3d/SimpleStraightSkel.h"
#include "algo/3d/GraphChecker.h"

#include "ui/gl/ptrs.h"
#include "ui/gl/MainOpenGLWindow.h"


using std::cout;
using std::endl;
using std::string;
using data::_2d::PolygonSPtr;
using data::_3d::PolyhedronSPtr;
using algo::Controller;
using algo::ControllerSPtr;
using ui::gl::MainOpenGLWindow;
using ui::gl::MainOpenGLWindowSPtr;


void printUsage(const char* argv0) {
    cout << "Usage: " << argv0 << " [2d|3d] [...] [GLUT_OPTIONS]" << endl;
    cout << endl;
    cout << "  2d options:" << endl;
    cout << "    PolygonID" << endl;
    cout << "    skel SkelID" << endl;
    cout << endl;
    cout << "  3d options:" << endl;
    cout << "    PolyhedronID" << endl;
    cout << "    load filename.obj" << endl;
    cout << "    import filename.obj" << endl;
    cout << "    skel SkelID" << endl;
    cout << endl;
    cout << "  general options:" << endl;
    cout << "    --no-window" << endl;
    cout << "    --save" << endl;
    cout << "    --config StraightSkel.ini" << endl;
    cout << endl;
    cout << "Example: " << argv0 << " 3d load anything.obj" << endl;
}

bool isSet(const char* option, int argc, const char* argv[]) {
    bool result = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], option) == 0) {
            result = true;
        }
    }
    return result;
}

const char* getOption(const char* option, int argc, const char* argv[]) {
    const char* result = 0;
    for (int i = 1; i < (argc-1); i++) {
        if (strcmp(argv[i], option) == 0) {
            result = argv[i+1];
        }
    }
    return result;
}


int main(int argc, const char* argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    // set number of dimensions
    int num_dims = 0;
    if (strcmp("2d", argv[1])==0 || strcmp("2", argv[1])==0) {
        num_dims = 2;
    } else if (strcmp("3d", argv[1])==0 || strcmp("3", argv[1])==0) {
        num_dims = 3;
    }
    if (num_dims < 2 || 3 < num_dims) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    util::ConfigurationSPtr config = util::Configuration::getInstance();
    string str_conf_file;
    const char* chr_conf_file = getOption("--config", argc, argv);
    if (chr_conf_file) {
        str_conf_file = chr_conf_file;
    } else {
        str_conf_file = config->findDefaultFilename();
    }
    if (!config->load(str_conf_file)) {
        cout << "Error: Config file '" << str_conf_file << "' not found." << endl;
        if (chr_conf_file) {
            return EXIT_FAILURE;
        }
    }

    bool rand_move_points = false;
    bool rand_move_points_when_degenerated = false;
    double rand_move_points_range = 0.001;
    bool translate_and_scale_polyhedron = false;
    bool translate_and_scale_view = false;
    float translate[3];
    for (unsigned int i = 0; i < 3; i++) {
        translate[i] = 0.0f;
    }
    float scale = 1.0f;
    if (config->isLoaded()) {
        rand_move_points = config->getBool("main", "rand_move_points");
        rand_move_points_when_degenerated =
                config->getBool("main", "rand_move_points_when_degenerated");
        double value = config->getDouble("main", "rand_move_points_range");
        if (value != 0.0) {
            rand_move_points_range = value;
        }
        translate_and_scale_polyhedron =
                config->getBool("main", "translate_and_scale_polyhedron");
        translate_and_scale_view =
                config->getBool("main", "translate_and_scale_view");
    }

    // load input
    int id = atoi(argv[2]);
    PolygonSPtr polygon;
    data::_2d::skel::StraightSkeletonSPtr skel2d;
    PolyhedronSPtr polyhedron;
    data::_3d::skel::StraightSkeletonSPtr skel3d;
    if (num_dims == 2) {
        db::_2d::PolygonDAOSPtr polygon_dao =
                db::_2d::DAOFactory::getPolygonDAO();
        if (strcmp("load", argv[2]) == 0) {
            const char* filename = argv[3];
            if (util::StringFuncs::endsWith(filename, ".flma")) {
                polygon = db::_2d::FLMAFile::load(filename);
            }
            if (!polygon) {
                cout << "Error: Unable to open '" << filename << "'." << endl;
                return EXIT_FAILURE;
            }
        } else if (strcmp("skel", argv[2]) == 0) {
            int skelid = atoi(argv[3]);
            db::_2d::StraightSkeletonDAOSPtr skel_dao =
                    db::_2d::DAOFactory::getStraightSkeletonDAO();
            skel2d = skel_dao->find(skelid);
            if (!skel2d) {
                cout << "Error: StraightSkeleton with SkelID=" << skelid
                    << " not found." << endl;
                return EXIT_FAILURE;
            } else {
                DEBUG_VAR(skel2d->toString());
                id = skel_dao->findPolyID(skelid);
                polygon = polygon_dao->find(id);
                if (polygon) {
                    skel2d->setPolygon(polygon);
                }
            }
        } else {
            polygon = polygon_dao->find(id);
            if (!polygon) {
                cout << "Error: Polygon with PolyID=" << id
                    << " not found." << endl;
                return EXIT_FAILURE;
            }
        }
        if (rand_move_points_when_degenerated && !rand_move_points) {
            cout << "Checking for parallel lines." << endl;
            if (algo::_2d::PolygonTransformation::hasParallelLines(polygon)) {
                cout << "Warning: Polygon has parallel lines." << endl;
                rand_move_points = true;
            }
        }
        if (rand_move_points) {
            cout << "Points will be moved randomly." << endl;
            algo::_2d::PolygonTransformation::randMovePoints(polygon, rand_move_points_range);
        }
        if (translate_and_scale_view) {
            data::_2d::Point2SPtr p_box_min =
                    algo::_2d::PolygonTransformation::boundingBoxMin(polygon);
            data::_2d::Point2SPtr p_box_max =
                    algo::_2d::PolygonTransformation::boundingBoxMax(polygon);
            float scale_min = std::numeric_limits<float>::max();
            for (unsigned int i = 0; i < 2; i++) {
                translate[i] = -((*p_box_max)[i] + (*p_box_min)[i])/2.0;
                float scale_cur = 20.0/((*p_box_max)[i] - (*p_box_min)[i]);
                if (scale_cur < scale_min) {
                    scale_min = scale_cur;
                }
                scale = scale_min;
            }
        }
        if (!polygon->isConsistent()) {
            cout << "Warning: Polygon with PolyID=" << id
                 << " is not consistent." << endl;
        }
        DEBUG_VAR(polygon->toString());
    } else if (num_dims == 3) {
        db::_3d::PolyhedronDAOSPtr polyhedron_dao =
                db::_3d::DAOFactory::getPolyhedronDAO();
        if (strcmp("test", argv[2]) == 0) {
            data::_3d::Point3SPtr p1 =
                    data::_3d::KernelFactory::createPoint3(-5.0, -5.0, -5.0);
            data::_3d::Point3SPtr p2 =
                    data::_3d::KernelFactory::createPoint3(5.0, 5.0, -5.0);
            data::_3d::Point3SPtr p3 =
                    data::_3d::KernelFactory::createPoint3(5.0, -5.0, 5.0);
            data::_3d::Point3SPtr p4 =
                    data::_3d::KernelFactory::createPoint3(-5.0, 5.0, 5.0);
            polyhedron = algo::_3d::PolyhedronBuilder::makeTetrahedron(
                    p1, p2, p3, p4);
        } else if (strcmp("load", argv[2]) == 0) {
            const char* filename = argv[3];
            if (util::StringFuncs::endsWith(filename, ".obj")) {
                polyhedron = db::_3d::OBJFile::load(filename);
            } else if (util::StringFuncs::endsWith(filename, ".flma")) {
                polyhedron = db::_3d::FLMAFile::load(filename);
            }
            if (!polyhedron) {
                cout << "Error: Unable to open '" << filename << "'." << endl;
                return EXIT_FAILURE;
            }
        } else if (strcmp("skel", argv[2]) == 0) {
            int skelid = atoi(argv[3]);
            db::_3d::StraightSkeletonDAOSPtr skel_dao =
                    db::_3d::DAOFactory::getStraightSkeletonDAO();
            skel3d = skel_dao->find(skelid);
            if (!skel3d) {
                cout << "Error: StraightSkeleton with SkelID=" << skelid
                    << " not found." << endl;
                return EXIT_FAILURE;
            } else {
                DEBUG_VAR(skel3d->toString());
                id = skel_dao->findPolyhedronID(skelid);
                polyhedron = polyhedron_dao->find(id);
                if (polyhedron) {
                    skel3d->setPolyhedron(polyhedron);
                }
            }
        } else if (strcmp("import", argv[2]) == 0) {
            polyhedron = db::_3d::OBJFile::load(argv[3]);
            if (!polyhedron) {
                cout << "Error: Polyhedron '" << argv[3] << "' not found."
                        << endl;
                return EXIT_FAILURE;
            }
            if (polyhedron->isConsistent()) {
                if (polyhedron_dao->insert(polyhedron) > 0) {
                    cout << argv[3] << " imported: PolyhedronID="
                            << polyhedron->getID() << endl;
                    return EXIT_SUCCESS;
                } else {
                    cout << "Error: Not able to import polyhedron." << endl;
                    return EXIT_FAILURE;
                }
            } else {
                cout << "Error: Polyhedron is not consistent and "
                        << "will not be imported." << endl;
                return EXIT_FAILURE;
            }
        } else {
            polyhedron = polyhedron_dao->find(id);
            if (!polyhedron) {
                cout << "Error: Polyhedron with PolyhedronID=" << id
                     << " not found." << endl;
                return EXIT_FAILURE;
            }
        }
        if (rand_move_points_when_degenerated && !rand_move_points) {
            cout << "Checking if all combinations of 3 facet supporting planes intersect in a point." << endl;
            cout << "In case this takes too long, "
                 << "you may disable 'rand_move_points_when_degenerated'." << endl;
            if (!algo::_3d::PolyhedronTransformation::doAll3PlanesIntersect(polyhedron)) {
                cout << "Warning: Not all combinations of 3 planes intersect." << endl;
                rand_move_points = true;
            }
        }
        if (translate_and_scale_polyhedron) {
            data::_3d::Point3SPtr p_box_min =
                    data::_3d::KernelFactory::createPoint3(-10.0, -10.0, -10.0);
            data::_3d::Point3SPtr p_box_max =
                    data::_3d::KernelFactory::createPoint3(10.0, 10.0, 10.0);
            algo::_3d::PolyhedronTransformation::translateNscale(
                    polyhedron, p_box_min, p_box_max);
        }
        if (rand_move_points) {
            cout << "Points will be moved randomly." << endl;
            algo::_3d::PolyhedronTransformation::randMovePoints(polyhedron, rand_move_points_range);
            string description = polyhedron->getDescription();
            polyhedron = algo::_3d::SimpleStraightSkel::shiftFacets(polyhedron, 0.0);
            polyhedron->clearData();
            polyhedron->setDescription(description);
        }
        if (translate_and_scale_view) {
            data::_3d::Point3SPtr p_box_min =
                    algo::_3d::PolyhedronTransformation::boundingBoxMin(polyhedron);
            data::_3d::Point3SPtr p_box_max =
                    algo::_3d::PolyhedronTransformation::boundingBoxMax(polyhedron);
            float scale_min = std::numeric_limits<float>::max();
            for (unsigned int i = 0; i < 3; i++) {
                translate[i] = -((*p_box_max)[i] + (*p_box_min)[i])/2.0;
                float scale_cur = 20.0/((*p_box_max)[i] - (*p_box_min)[i]);
                if (scale_cur < scale_min) {
                    scale_min = scale_cur;
                }
                scale = scale_min;
            }
        }
        if (!polyhedron->isConsistent()) {
            cout << "Warning: Polyhedron with PolyhedronID=" << id
                 << " is not consistent." << endl;
        }
        DEBUG_VAR(polyhedron->toString());
    }

    // create OpenGL window
    bool no_window = isSet("--no-window", argc, argv);
    ControllerSPtr controller;
    MainOpenGLWindowSPtr window;
    if (!no_window) {
        controller = Controller::create();
        controller->togglePause();
        int width = config->getInt("ui_gl_MainOpenGLWindow", "width");
        if (width == 0) {
            width = 800;
        }
        int height = config->getInt("ui_gl_MainOpenGLWindow", "height");
        if (height == 0) {
            height = 600;
        }
        window = MainOpenGLWindow::create(argc, argv, width, height, controller);
    }

    // run algorithm
    // has to be in this scope otherwise the algorithm will be destroyed
    ThreadSPtr thread_algo;
    ThreadSPtr thread_window;
    algo::_2d::SimpleStraightSkelSPtr algoskel2d;
    algo::_3d::SimpleStraightSkelSPtr algoskel3d;
    if (num_dims == 2) {
        algoskel2d =
                algo::_2d::SimpleStraightSkel::create(polygon, controller);
        if (window) {
            window->setPolygon(polygon);
            if (skel2d) {
                window->setSkel2d(skel2d);
            }
            thread_algo = algoskel2d->startThread();
        } else {
            algoskel2d->run();
        }
    } else if (num_dims == 3) {
        algoskel3d =
                algo::_3d::SimpleStraightSkel::create(polyhedron, controller);
        if (window) {
            window->setPolyhedron(polyhedron);
            if (skel3d) {
                window->setSkel3d(skel3d);
            }
            thread_algo = algoskel3d->startThread();
        } else {
            algoskel3d->run();
        }
    }
    if (window) {
        if (translate_and_scale_view) {
            window->setTranslate(translate);
            window->setScale(scale);
        }
        thread_window = window->startThread();
        thread_algo->join();
    }

    bool save = isSet("--save", argc, argv);
    if (save) {
        if (num_dims == 2) {
            skel2d = algoskel2d->getResult();
            if (skel2d) {
                db::_2d::DAOFactory::getPolygonDAO()->insert(polygon);
                db::_2d::DAOFactory::getStraightSkeletonDAO()->insert(skel2d);
                cout << "SkelID=" << skel2d->getID() << endl;
            }
        } else if (num_dims == 3) {
            skel3d = algoskel3d->getResult();
            if (skel3d) {
                db::_3d::DAOFactory::getPolyhedronDAO()->insert(polyhedron);
                db::_3d::DAOFactory::getStraightSkeletonDAO()->insert(skel3d);
                cout << "SkelID=" << skel3d->getID() << endl;
            }
        }
    }

    algo::_2d::SkelMeshGeneratorSPtr algomesh2d;
    bool create_mesh = isSet("--mesh", argc, argv);
    if (create_mesh) {
        controller->wait();
        if (num_dims == 2) {
            skel2d = algoskel2d->getResult();
            algomesh2d = algo::_2d::SkelMeshGenerator::create(skel2d, controller);
            if (window) {
                window->setMesh2d(algomesh2d->getResult());
                thread_algo = algomesh2d->startThread();
            } else {
                algomesh2d->run();
            }
        }
    }

    if (isSet("--check-graph", argc, argv) && num_dims == 3) {
        algo::_3d::GraphCheckerSPtr graphchecker = algo::_3d::GraphChecker::create();
        skel3d = algoskel3d->getResult();
        graphchecker->check(skel3d);
    }

    if (window) {
        thread_window->join();
    }

    return EXIT_SUCCESS;
}

