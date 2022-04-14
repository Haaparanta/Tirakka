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
#include <utility>
#include <algorithm>
#include <QSqlDatabase>
#include <QSqlQuery>

// Types for IDs
using PlaceID = long int;
using AreaID = long int;
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

    // Estimate of performance: O(1)
    // Short rationale for estimate: bc size().
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: linear bc for loop
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: linear bc for loop
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(n)
    // Short rationale for estimate: using of count to check if there is key already
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: best: O(1) worst O(n)
    // Short rationale for estimate: bc at()
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(1) worst O(n)
    // Short rationale for estimate: bc calling at()
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: mostly O(n), but at worst O(n²)
    // Short rationale for estimate: bc functio have to go trough a map and a vector
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: mostly O(n), but at worst O(n²)
    // Short rationale for estimate: for loop inside for loop
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: linear bc of for loop
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: linear bc of for loop
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: best: O(1) worst: O(n)
    // Short rationale for estimate: bc at().
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(1) worst: O(n)
    // Short rationale for estimate: bc at().
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:best O(1) worst O(n)
    // Short rationale for estimate: count()
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: best: O(1) worst: O(n)
    // Short rationale for estimate: at()
    Name get_area_name(AreaID id);

    // Estimate of performance: best: O(1) worst: O(n)
    // Short rationale for estimate: at()
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: linear bc of for loop
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(n)
    // Short rationale for estimate: bc count()
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: while loop
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance: O(n)
    // Short rationale for estimate: linear bc for loop
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: best: O(1) worst: O(n)
    // Short rationale for estimate: at()
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n)
    // Short rationale for estimate: count and erase
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n*n)
    // Short rationale for estimate: bc of dual for loop
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

private:
    // Add stuff needed for your class implementation here
    struct Place {
        PlaceID id;
        Name name;
        PlaceType type;
        Coord coords;
    };

    struct Area {
        AreaID id;
        Name name;
        std::vector<Coord> coords;
        std::vector<AreaID> sooubway;
        AreaID henpecked = NO_AREA;
    };

    std::unordered_map<PlaceID, Place*> placeById;
    std::map<Name, std::vector<Place*>> placeByName;
    std::map<PlaceType, std::vector<Place*>> placeByType;

    std::unordered_map<PlaceID, Area*> areaById;
    std::map<Name, std::vector<Area*>> areaByName;

    double distance(Coord xy1, Coord xy2);

};

#endif // DATASTRUCTURES_HH
