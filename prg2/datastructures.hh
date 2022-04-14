// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>

#include <map>
#include <unordered_map>
#include <memory>
#include <utility>
#include <math.h>
#include <algorithm>
#include <queue>

#include <QDebug>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement


class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: linear always
    void clear_all();

    // Estimate of performance:O(n)
    // Short rationale for estimate: for loop and push_back is constant
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: insert average constant, but worst case o(n)
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find constant average, but linear worst
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find constant average, but linear worst
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(nlogn)
    // Short rationale for estimate: multimap insert log(n) and loop is linear
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: multimap insert log(n) and loop is linear
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: equalrange average linear size of result and worst case size of container
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: equalrange average linear size of result and worst case size of container
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: insert average constant, but worst case o(n)
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    Name get_area_name(AreaID id);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate: for loop and push_back is constant
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    // and while loop
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance: Super fast
    // Short rationale for estimate: Not implemented
    void creation_finished();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: in getAllChildren there is two for loops and it is recursive
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: O(n) average, but O(^2) worst case
    // Short rationale for estimate: loop and inside loop find which worst case is linear
    // find is inside loop
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: in getAllChildren there is two for loops and it is recursive
    // and there is two for loops indide each other
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: for loop, but the loop is just size of given vector of coordinates
    // there is also find and insert which worst case is linear
    std::vector<WayID> all_ways();

    // Estimate of performance: O(n)
    // Short rationale for estimate: for loop, but the loop is just size of given vector of coordinates
    // there is also find and insert which worst case is linear
    bool add_way(WayID id, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: for loop and push_back which is constant
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);

    // Estimate of performance: O(n) average O(1)
    // Short rationale for estimate: find average constant and worst linear
    std::vector<Coord> get_way_coords(WayID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: clear is always linear
    void clear_ways();

    // Estimate of performance: O(n)
    // Short rationale for estimate: use of find which has worst case of linear
    // and also for loop and second for loop inside DFS algo
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);

    // Non-compulsory operations

    // Estimate of performance: O(n) worst and O(1) average
    // Short rationale for estimate: lots of use of find and erase
    bool remove_way(WayID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: There is for loop inside while loop in BFS algo
    std::vector<std::tuple<Coord, WayID, Distance>> route_least_crossroads(Coord fromxy, Coord toxy);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: There is for loop inside while loop in BFS algo
    std::vector<std::tuple<Coord, WayID>> route_with_cycle(Coord fromxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_shortest_distance(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_ways();

private:
    struct Place {
        Place(PlaceID id, Name name, PlaceType type, Coord coordinate):
            id(id),
            name(name),
            type(type),
            coordinate(coordinate)
        {}
        PlaceID id;
        Name name;
        PlaceType type;
        Coord coordinate;
    };

    struct Area {
        Area(AreaID id, Name name, std::vector<Coord> coordinates):
            id(id),
            name(name),
            coordinates(coordinates),
            parent(nullptr),
            children({})
        {}
        AreaID id;
        Name name;
        std::vector<Coord> coordinates;
        std::shared_ptr<Area> parent;
        std::vector<std::weak_ptr<Area>> children;
    };

    struct Way {
        Way(WayID id, std::vector<Coord> coordinates, Distance distance):
            id(id),
            coordinates(coordinates),
            distance(distance)
        {}
        WayID id = NO_WAY;
        std::vector<Coord> coordinates;
        Distance distance = 0;
    };

    struct Crossroad {
        Crossroad(Coord coordinates):
            coordinates(coordinates)
        {}
        bool visited = false;
        Coord coordinates = NO_COORD;
        std::unordered_multimap<std::shared_ptr<Crossroad>, std::shared_ptr<Way>> connections;
        std::shared_ptr<Crossroad> parent = nullptr;
    };

    std::unordered_map<PlaceID, std::shared_ptr<Place>> placeById_;
    std::unordered_map<AreaID, std::shared_ptr<Area>> areaById_;
    std::unordered_map<WayID, std::shared_ptr<Way>> wayById_;
    std::unordered_map<Coord, std::shared_ptr<Crossroad>, CoordHash> crossByHash_;

    std::vector<PlaceID> placesByNameOrder_;
    bool name_flag_;
    std::vector<PlaceID> placesByCoordsOrder_;
    bool coord_flag_;

    //DFS
    std::vector<Coord> stack_;
    std::vector<Coord> result_;

    //BFS
    bool bfsFlag = false;


    // new cycle
    Coord startCycle_;
    Coord endCycle_;
    std::vector<Coord> cycle_;
    std::unordered_map<Coord, Coord, CoordHash> parent_;

    double distance(Coord xy1, Coord xy2); //return double
    int wayDistance(Coord xy1, Coord xy2); // return int almous same
    std::vector<AreaID> getAllChildren(std::shared_ptr<Area> area); // get all area children
    void visited(); // visited to false and remove parents
    void DFS(Coord fromxy, Coord toxy);// algo
    void BFS(Coord fromxy, Coord toxy);// algo
    void toVector(Coord fromxy, Coord toxy);
    bool detectCycle(Coord node, Coord parent);// check if cycle
    void findSimpleCycle(Coord start, Coord end); // find cycle
    WayID getWay(Coord fromxy, Coord toxy); // get way by nodes
};


#endif // DATASTRUCTURES_HH
