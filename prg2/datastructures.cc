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
    return placeById_.size();
}

void Datastructures::clear_all()
{
    placeById_.clear();
    areaById_.clear();
    coord_flag_ = true;
    name_flag_ = true;
}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> places;
    for ( auto it = placeById_.begin() ; it != placeById_.end() ; ++it){
        places.push_back(it->first);
    }
    return {places};
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    std::shared_ptr<Place> place = std::make_shared<Place>(id, name, type, xy);
    if (placeById_.insert({id, place}).second) {
        coord_flag_ = true;
        name_flag_ = true;
        return true;
    }
    return false;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    auto it = placeById_.find(id);
    if (it != placeById_.end()) {
        return {it->second->name, it->second->type};
    }
    return {NO_NAME, PlaceType::NO_TYPE};
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    auto it = placeById_.find(id);
    if (it != placeById_.end()) {
        return it->second->coordinate;
    }
    return NO_COORD;
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    std::shared_ptr<Area> area = std::make_shared<Area>(id, name, coords);
    if (areaById_.insert({id, area}).second) {
        return true;
    }
    return false;
}

Name Datastructures::get_area_name(AreaID id)
{
    auto it = areaById_.find(id);
    if (it != areaById_.end()) {
        return it->second->name;
    }
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    auto it = areaById_.find(id);
    if (it != areaById_.end()) {
        return it->second->coordinates;
    }
    return {NO_COORD};
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{
    if (name_flag_) {
        // makes multimap from unorderedmultimap. bc rather then making sure it always in order
        // just when this functio is called.
        std::multimap<Name, std::shared_ptr<Place>> tempMap;
        placesByNameOrder_.clear();
        for ( auto it = placeById_.begin() ; it != placeById_.end() ; ++it ){
            tempMap.insert({it->second->name, it->second});
        }
        for (auto it = tempMap.begin() ; it != tempMap.end() ; ++it) {
            placesByNameOrder_.push_back(it->second->id);
        }
    }
    name_flag_ = false;
    return placesByNameOrder_;
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    if (coord_flag_) {
        // makes multimap from unorderedmultimap. bc rather then making sure it always in order
        // just when this functio is called.
        std::multimap<long double, std::shared_ptr<Place>> tempMap;
        placesByCoordsOrder_.clear();
        double x, y, z, c;
        for ( auto it = placeById_.begin() ; it != placeById_.end() ; ++it ){
            x = it->second->coordinate.x;
            y = it->second->coordinate.y;
            c = pow(x,2) + pow(y,2);
            z = sqrt(c);
            tempMap.insert({z, it->second});
        }
        for (auto it = tempMap.begin() ; it != tempMap.end() ; ++it) {
            placesByCoordsOrder_.push_back(it->second->id);
        }
    }
    coord_flag_ = false;
    return placesByCoordsOrder_;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> places;
    for ( auto it = placeById_.begin(); it != placeById_.end(); ++it) {
        if (it->second->name == name) {
            places.push_back(it->second->id);
        }
    }
    return places;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> places;
    for ( auto it = placeById_.begin(); it != placeById_.end(); ++it) {
        if (it->second->type == type) {
            places.push_back(it->second->id);
        }
    }
    return places;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    auto place = placeById_.find(id);
    if (place != placeById_.end()) {
        place->second->name = newname;
        name_flag_ = true;
        return true;
    }
    return false;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    auto place = placeById_.find(id);
    if (place != placeById_.end()) {
        place->second->coordinate = newcoord;
        coord_flag_ = true;
        return true;
    }
    return false;
}

std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<AreaID> areas;
    for ( auto it = areaById_.begin(); it != areaById_.end(); ++it) {
        areas.push_back(it->second->id);
    }
    return areas;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    auto area = areaById_.find(id);
    auto parent = areaById_.find(parentid);
    if (area == areaById_.end()) return false;
    if (parent == areaById_.end()) return false;
    if (area->second->parent != nullptr) return false;
    area->second->parent = parent->second;
    parent->second->children.push_back(area->second);
    return true;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    auto it = areaById_.find(id);
    if (it == areaById_.end()) return {NO_AREA};
    auto area = it->second;
    std::vector<AreaID> areas;
    while (area->parent != nullptr) {
        areas.push_back(area->parent->id);
        area = area->parent;
    }
    return areas;
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    std::multimap<int, PlaceID> PLACES;
    std::vector<PlaceID> places;
    double temp;
    if (type == PlaceType::NO_TYPE) {
        for (auto it = placeById_.begin(); it != placeById_.end(); ++it) {
            temp = distance(xy, it->second->coordinate);
            PLACES.insert({temp, it->second->id});
        }
    } else {
        for (auto it = placeById_.begin(); it != placeById_.end(); ++it) {
            if (it->second->type == type) {
                temp = distance(xy, it->second->coordinate);
                PLACES.insert({temp, it->second->id});
            }
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
    auto place = placeById_.find(id);
    if (place == placeById_.end()) return false;
    coord_flag_ = true;
    name_flag_ = true;
    placeById_.erase(id);
    return true;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    auto it = areaById_.find(id);
    if (it == areaById_.end()) return {NO_AREA};
    return getAllChildren(it->second);
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    if (areaById_.find(id1) == areaById_.end() or areaById_.find(id2) == areaById_.end()) return NO_AREA;
    std::vector<AreaID> areas1 = subarea_in_areas(id1);
    std::vector<AreaID> areas2 = subarea_in_areas(id2);
    for (unsigned int i = 0; i < areas1.size(); ++i) {
        for (unsigned int j = 0; j < areas2.size(); ++j) {
            if (areas1.at(i) == areas2.at(j)) {
                return areas1.at(i);
            }
        }
    }
    return NO_AREA;
}

std::vector<WayID> Datastructures::all_ways()
{
    std::vector<WayID> ways;
    for (auto it = wayById_.begin(); it != wayById_.end(); ++it) {
        ways.push_back(it->second->id);
    }
    return ways;
}

bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{   
    std::shared_ptr<Way> way = std::make_shared<Way>(id, coords, NO_DISTANCE);
    std::shared_ptr<Crossroad> start = nullptr;
    std::shared_ptr<Crossroad> end = nullptr;
    if (wayById_.insert({id, way}).second) {
        if (crossByHash_.find(coords.front()) == crossByHash_.end()) {
            start = std::make_shared<Crossroad>(coords.front());
        }
        if (crossByHash_.find(coords.back()) == crossByHash_.end()) {
            end = std::make_shared<Crossroad>(coords.back());
        }
        int lenght = 0;
        for (unsigned int i = 0; i < coords.size()-1; ++i) {
            lenght += wayDistance(coords.at(i), coords.at(i+1));
        }
        way->distance = lenght;
        if (start != nullptr) {
            if (end != nullptr) {
                start->connections.insert({end, way});
                end->connections.insert({start, way});
            } else {
                std::shared_ptr<Crossroad> it = crossByHash_.find(coords.back())->second;
                start->connections.insert({it, way});
                it->connections.insert({start, way});
            }
        } else {
            if (end != nullptr) {
                std::shared_ptr<Crossroad> it = crossByHash_.find(coords.front())->second;
                end->connections.insert({it, way});
                it->connections.insert({end, way});
            } else {
                std::shared_ptr<Crossroad> it = crossByHash_.find(coords.front())->second;
                std::shared_ptr<Crossroad> iter = crossByHash_.find(coords.back())->second;
                it->connections.insert({iter, way});
                iter->connections.insert({it, way});
            }
        }
        if (start != nullptr) crossByHash_.insert({coords.front(), start});
        if (end != nullptr) crossByHash_.insert({coords.back(), end});
        return true;
    }
    return false;
}

std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{
    auto it = crossByHash_.find(xy);
    if (it == crossByHash_.end()) return {};
    std::vector<std::pair<WayID, Coord>> things;
    for (auto iter = it->second->connections.begin(); iter != it->second->connections.end(); ++iter) {
        things.push_back({iter->second->id, iter->first->coordinates});
    }
    if (things.empty()) return {{NO_WAY, NO_COORD}};
    return things;
}

std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    auto it = wayById_.find(id);
    if (it != wayById_.end()) {
        return it->second->coordinates;
    }
    return {NO_COORD};
}

void Datastructures::clear_ways()
{
    wayById_.clear();
    crossByHash_.clear();
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord fromxy, Coord toxy)
{

    auto start = crossByHash_.find(fromxy);
    auto end = crossByHash_.find(toxy);
    if (start == crossByHash_.end()) return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    if (end == crossByHash_.end()) return {{NO_COORD, NO_WAY, NO_DISTANCE}};

    std::vector<std::tuple<Coord, WayID, Distance>> travel;
    stack_.clear();
    result_.clear();
    visited();
    DFS(fromxy, toxy);
    if (result_.back() != toxy) return {};
    int lenght;
    for (unsigned int i = 0; i < result_.size(); ++i) {
        if (i == 0) {
            auto temp = std::make_tuple(result_.at(0), "lol", 0);
            travel.push_back(temp);
        } else if (result_.at(i) == toxy ){
            lenght += wayById_.find(getWay(result_.at(i), result_.at(i-1)))->second->distance;
            auto temp = std::make_tuple(result_.at(i), NO_WAY, lenght);
            travel.push_back(temp);
        } else {
            lenght += wayById_.find(getWay(result_.at(i), result_.at(i-1)))->second->distance;
            auto temp = std::make_tuple(result_.at(i), "lol", lenght);
            travel.push_back(temp);
        }
    }
    return travel;
}

bool Datastructures::remove_way(WayID id)
{
    auto way = wayById_.find(id);
    if (way == wayById_.end()) return false;
    auto sNode = crossByHash_.find(way->second->coordinates.front());
    auto eNode = crossByHash_.find(way->second->coordinates.back());
    if (sNode->second->connections.size() < 2) {
         crossByHash_.erase(way->second->coordinates.front());
    } else sNode->second->connections.erase(eNode->second);
    if (eNode->second->connections.size() < 2) {
        crossByHash_.erase(way->second->coordinates.back());
    } else eNode->second->connections.erase(sNode->second);
    wayById_.erase(way);
    return true;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_least_crossroads(Coord fromxy, Coord toxy)
{
    auto start = crossByHash_.find(fromxy);
    auto end = crossByHash_.find(toxy);
    if (start == crossByHash_.end()) return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    if (end == crossByHash_.end()) return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    visited();
    bfsFlag = false;
    BFS(fromxy, toxy);
    if (!bfsFlag) return {};
    std::vector<std::tuple<Coord, WayID, Distance>> travel;
    int lenght = 0;
    result_.clear();
    toVector(fromxy, toxy);
    for (unsigned int i = 0; i < result_.size(); ++i) {
        if (i == 0) {
            WayID way = getWay(result_.at(0), result_.at(1));
            auto temp = std::make_tuple(result_.at(0), way, 0);
            travel.push_back(temp);
        } else if (result_.at(i) == toxy ){
            lenght += wayById_.find(getWay(result_.at(i), result_.at(i-1)))->second->distance;
            auto temp = std::make_tuple(result_.at(i), NO_WAY, lenght);
            travel.push_back(temp);
        } else {
            WayID way = getWay(result_.at(i), result_.at(i+1));
            lenght += wayById_.find(getWay(result_.at(i), result_.at(i-1)))->second->distance;
            auto temp = std::make_tuple(result_.at(i), way, lenght);
            travel.push_back(temp);
        }
    }
    return travel;
}

std::vector<std::tuple<Coord, WayID> > Datastructures::route_with_cycle(Coord fromxy)
{
    auto start = crossByHash_.find(fromxy);
    if (start == crossByHash_.end()) return {{NO_COORD, NO_WAY}};
    visited();
    bool found = detectCycle(fromxy, NO_COORD);
    if (!found) return {};
    visited();
    cycle_.clear();
    parent_.clear();
    std::vector<std::tuple<Coord, WayID>> travel;
    cycle_.push_back(endCycle_);
    findSimpleCycle(startCycle_, endCycle_);
    unsigned int rev = cycle_.size() - 1;

    auto temp = std::make_tuple(fromxy, NO_WAY);
    travel.push_back(temp);
    for (unsigned int i = 0; i < cycle_.size(); ++i) {
        if (i == rev) {
            auto node1 = crossByHash_.find(cycle_.at(rev - 0))->second;
            auto node2 = crossByHash_.find(cycle_.at(rev - 1))->second;
            WayID way = node1->connections.find(node2)->second->id;
            auto temp = std::make_tuple(cycle_.at(rev - 0), way);
            travel.push_back(temp);
        } else {
            auto node1 = crossByHash_.find(cycle_.at(rev - i))->second;
            auto node2 = crossByHash_.find(cycle_.at(rev - i-1))->second;
            WayID way = node1->connections.find(node2)->second->id;
            auto temp = std::make_tuple(cycle_.at(rev - i), way);
            travel.push_back(temp);
        }
    }
    return travel;

}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_shortest_distance(Coord fromxy, Coord toxy)
{
    // This is undirected weighted graph and could easily solve by bfs finding first way
    // which is also shortest way
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

Distance Datastructures::trim_ways()
{
    // I wuold run bsf and until all nodes are visited. Then use parent info to safe
    // and then removeWay all the unused ways.
    return NO_DISTANCE;
}

double Datastructures::distance(Coord xy1, Coord xy2)
{
    return sqrt(pow((xy1.x-xy2.x),2) + pow((xy1.y-xy2.y), 2));
}

int Datastructures::wayDistance(Coord xy1, Coord xy2)
{
    double x = pow((xy1.x-xy2.x),2);
    double y = pow((xy1.y-xy2.y), 2);
    return sqrt(x+y);
}

std::vector<AreaID> Datastructures::getAllChildren(std::shared_ptr<Area> area)
{
    if (area->children.size() == 0) return {};
    std::vector<AreaID> areas;
    for ( auto it = area->children.begin(); it != area->children.end(); ++it) {
        std::vector<AreaID> temp = getAllChildren(it->lock());
        for (auto it : temp) areas.push_back(it);
        areas.push_back(it->lock()->id);
    }
    return areas;
}

void Datastructures::visited()
{
    for (auto it = crossByHash_.begin(); it != crossByHash_.end(); ++it) {
        it->second->visited = false;
        it->second->parent = nullptr;
    }
}

void Datastructures::DFS(Coord fromxy, Coord toxy)
{
    stack_.push_back(fromxy);
    if (fromxy == toxy) {
        result_ = stack_;
        return;
    }
    auto node = crossByHash_.find(fromxy);
    node->second->visited = true;
    if (!node->second->connections.empty()) {
        for (auto cross : node->second->connections) {
            if (!cross.first->visited) {
                DFS(cross.first->coordinates, toxy);
            }
        }
    }
    stack_.pop_back();
}

void Datastructures::BFS(Coord fromxy, Coord toxy)
{
    std::queue<Coord> que;
    que.push(fromxy);
    if (fromxy == toxy) {
        bfsFlag = true;
        return;
    }
    while (!que.empty()) {
        auto curr = que.front();
        que.pop();
        if (curr == toxy) {
            bfsFlag = true;
            break;
        }
        auto node = crossByHash_.find(curr);
        for (auto cross : node->second->connections) {
            if (!cross.first->visited) {
                cross.first->visited = true;
                que.push(cross.first->coordinates);
                cross.first->parent = crossByHash_.find(curr)->second;
            }
        }
    }
}

void Datastructures::toVector(Coord fromxy, Coord toxy)
{
    auto node = crossByHash_.find(toxy)->second;
    if (fromxy == toxy) {
        result_.push_back(node->coordinates);
        return;
    }
    toVector(fromxy, node->parent->coordinates);
    result_.push_back(node->coordinates);
}

bool Datastructures::detectCycle(Coord node_, Coord parent_)
{
    auto node = crossByHash_.find(node_)->second;
    node->visited = true;
    for (auto child : node->connections) {
        if (!child.first->visited) {
            if (detectCycle(child.first->coordinates, node_)) {
                return true;
            }
        else if (child.first->coordinates != parent_) {
                startCycle_ = child.first->coordinates;
                endCycle_ = node_;
                return true;
            }
        }
    }
    return false;
}

void Datastructures::findSimpleCycle(Coord start, Coord end)
{
    std::queue<Coord> que;
    que.push(start);
    bool ok = true;
    while (!que.empty()) {
        auto curr = que.front();
        que.pop();
        auto node = crossByHash_.find(curr);
        node->second->visited = true;
        for (auto child : node->second->connections) {
            if (child.first->coordinates == end && node->second->coordinates == start) {
                continue;
            }
            if (!child.first->visited) {
                parent_.insert({child.first->coordinates, node->second->coordinates});
                if (child.first->coordinates == end) {
                    ok = false;
                    break;
                }
                que.push(child.first->coordinates);
                child.first->visited = true;
            }
        }
        if (!ok) {
            break;
        }
    }
    cycle_.push_back(start);
    Coord temp = end;
    while (temp != start) {
        cycle_.push_back(temp);
        temp = parent_.at(temp);
    }
}

WayID Datastructures::getWay(Coord fromxy, Coord toxy)
{
    auto node1 = crossByHash_.find(fromxy)->second;
    auto node2 = crossByHash_.find(toxy)->second;
    return node1->connections.find(node2)->second->id;
}


