// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::place_count()
{
    return placeById.size();
}

void Datastructures::clear_all()
{
    for (auto it : placeById) {
        delete it.second;
    }
    placeById.clear();
    placeByName.clear();
    placeByType.clear();
    for (auto it : areaById) {
        delete  it.second;
    }
    areaById.clear();
    areaByName.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> PLACE;
    for (auto it : placeById) {
        PLACE.push_back(it.first);
    }
    return PLACE;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    if (placeById.count(id)) {
        return false;
    } else {
        Place* PLACE = new Place({id, name, type, xy});
        placeById.insert({id, PLACE});
        auto result = placeByName.insert({name, {PLACE}});
        if (!result.second) {
            placeByName.at(name).push_back(PLACE);
        }
        auto res = placeByType.insert({type, {PLACE}});
        if (!res.second) {
            placeByType.at(type).push_back(PLACE);
        }
    }
    return true;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    // Replace this comment with your implementation
    Name NAME = placeById.at(id)->name;
    PlaceType placetype = placeById.at(id)->type;
    if (NAME == "") {
        return {NO_NAME, PlaceType::NO_TYPE};
    }
    return {NAME, placetype};
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    Coord coor = placeById.at(id)->coords;
    if (coor.x != NO_VALUE) {
        return coor;
    }
    return NO_COORD;
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    if (areaById.count(id)) {
        return false;
    }
    Area* AREA = new Area{id, name, coords, {}};
    areaById.insert({id, AREA});
    if (areaByName.count(name)) {
        areaByName.at(name).push_back(AREA);
    } else {
        areaByName.insert({name, {AREA}});
    }
    return true;
}

Name Datastructures::get_area_name(AreaID id)
{
    Name NAME = areaById.at(id)->name;
    if (NAME == "") {
        return NO_NAME;
    }
    return NAME;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    std::vector<Coord> coords = areaById.at(id)->coords;
    if (coords.empty()) {
        return {NO_COORD};
    }
    return coords;
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{
    std::vector<PlaceID> PLACE;
    for (auto it : placeByName) {
        for (unsigned int i = 0; i < it.second.size(); ++i) {
            if (placeById.count(it.second.at(i)->id)) {
                if (!std::count(PLACE.begin(), PLACE.end(), it.second.at(i)->id)) { //it.second.at(i) != nullptr &&
                    PLACE.push_back(it.second.at(i)->id);
                }
            }
        }
    }
    return PLACE;
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::map<long double, std::vector<PlaceID>> PLACE;
    double x, y, z, c;
    for (auto it : placeById) {
        x = it.second->coords.x;
        y = it.second->coords.y;
        c = pow(x,2) + pow(y,2);
        z = sqrt(c);
        if (PLACE.count(z)) {
            PLACE.at(z).push_back(it.first);
        } else {
            PLACE.insert({z, {it.first}});
        }
    }
    std::vector<PlaceID> placeids;
    for (auto it : PLACE) {
        for (auto is : it.second) {
            placeids.push_back(is);
        }
    }
    return placeids;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    if (!placeByName.count(name)) return {};
    std::vector<PlaceID> places;
    PlaceID z;
    for (unsigned int i = 0 ; i < placeByName.at(name).size(); ++i) {
        if (placeById.count(placeByName.at(name).at(i)->id)) {
            z =placeByName.at(name).at(i)->id;
            if (placeById.at(z)->name == name) places.push_back(z);
        }
    }
    return places;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    if (!placeByType.count(type)) return {};
    std::vector<PlaceID> places;
    for (auto it : placeByType.at(type)) {
        if (placeById.count(it->id)) {
            places.push_back(it->id);
        }
    }
    return places;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    if (placeById.at(id)) {
        placeById.at(id)->name = newname;
        auto result = placeByName.insert({newname, {placeById.at(id)}});
        if (!result.second) {
            placeByName.at(newname).push_back(placeById.at(id));
        }
        return true;
    }
    return false;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    if (placeById.at(id)) {
        placeById.at(id)->coords = newcoord;
        return true;
    }
    return false;
}

std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<AreaID> AREAS;
    for (auto it : areaById) {
        AREAS.push_back(it.second->id);
    }
    return AREAS;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    if (areaById.at(id)->henpecked !=  NO_AREA) {
        return false;
    } else if (!areaById.count(id)) {
        return false;
    } else if (!areaById.count(parentid)) {
        return false;
    }
    areaById.at(parentid)->sooubway.push_back(id);
    areaById.at(id)->henpecked = parentid;
    return true;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    std::vector<AreaID> AREAS;
    AreaID temp = id;
    while (temp != NO_AREA) {
        temp = areaById.at(temp)->henpecked;
        if (temp != NO_AREA) AREAS.push_back(temp);
    }
    if (AREAS.empty()) return {}; // doc tells that return NO_AREA and test say return empty
    return AREAS;
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    std::multimap<int, PlaceID> PLACES;
    std::vector<PlaceID> places;
    double temp;
    if (type == PlaceType::NO_TYPE) {
        for (auto it : placeById) {
            temp = distance(xy, it.second->coords);
            PLACES.insert({temp, it.second->id});
        }
    } else {
        for (auto it : placeByType.at(type)) {
            temp = distance(xy, it->coords);
            PLACES.insert({temp, it->id});
        }
    }
    int i = 0;
    for (auto it : PLACES) {
        places.push_back(it.second);
        ++i;
        if (i > 2) {
            break;
        }
    }
    return {places};
}

bool Datastructures::remove_place(PlaceID id)
{
    if (!placeById.count(id)) return false;
    Place* place = placeById.at(id);
    std::vector<Place*> PLACES = placeByName.at(place->name);
    auto it = std::find(PLACES.begin(), PLACES.end(), place);
    if (it != PLACES.end()) {
      std::swap(*it, PLACES.back());
      PLACES.pop_back();
    }
    PLACES.clear();
    PLACES = placeByType.at(place->type);
    it = std::find(PLACES.begin(), PLACES.end(), place);
    if (it != PLACES.end()) {
      std::swap(*it, PLACES.back());
      PLACES.pop_back();
    }
    delete place;
    placeById.erase(id);
    return true;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    if (!areaById.count(id)) {
        return {NO_AREA};
    }
    if (areaById.at(id)->sooubway.empty()) {
        return {};
    }
    std::vector<AreaID> AREAS = areaById.at(id)->sooubway;
    int temp = AREAS.size();
    for (int i = 0; i < temp; ++i) {
        if (!areaById.at(AREAS.at(i))->sooubway.empty()) {
            AREAS.insert(AREAS.end(), areaById.at(AREAS.at(i))->sooubway.begin(),
                         areaById.at(AREAS.at(i))->sooubway.end());
            temp += areaById.at(AREAS.at(i))->sooubway.size();
        }
    }
    return AREAS;
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    if (!areaById.count(id1)) {
        return NO_AREA;
    } else if (!areaById.count(id2)) {
        return NO_AREA;
    }
    std::vector<AreaID> AREAS1 = subarea_in_areas(id1);
    std::vector<AreaID> AREAS2 = subarea_in_areas(id2);
    for (unsigned int i = 0; i < AREAS1.size(); ++i) {
        for (unsigned int j = 0; j < AREAS2.size(); ++j) {
            if (AREAS1.at(i) == AREAS2.at(j)) {
                return AREAS1.at(i);
            }
        }
    }
    return NO_AREA;
}

double Datastructures::distance(Coord xy1, Coord xy2)
{
    return sqrt(pow((xy1.x-xy2.x),2) + pow((xy1.y-xy2.y), 2));
}



// ok testread "../prg1/example-compulsory-in.txt" "../prg1/example-compulsory-out.txt"
// ok testread "../prg1/example-all-in.txt" "../prg1/example-all-out.txt"
// ok testread "../prg1/kintulammi-test-compulsory-in.txt" "../prg1/kintulammi-test-compulsory-out.txt"
// ok testread "../prg1/kintulammi-test-all-in.txt" "../prg1/kintulammi-test-all-out.txt"

