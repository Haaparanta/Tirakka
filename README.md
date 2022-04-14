Huom toteutin tähän harjoitustyöhön ykkösosion uudestaan, 
koska sain viime kerralla arvosanan 
1 ja haluaisin saada siitä paremman.

Olen toteuttannut tämän ohjelman funktiot loppuun käyttäen 4 structia, 
mappeja ja luonut omia funktioita.
Olen täyttänyt funktioit käyttäen ohjelmoinnin perusperiaateita. Jotka ovat:
1. luettavuus
2. tehokkuus
3. yksinkertaisuus
4. skaalatavuus
5. rinnakaisuus
Tämän kurssin tavoite keskittyä tehokuuteen. 
Olen onnistunut tässä koska suurin osa funktioista on toteuttettu välille vakioajasta lineaariseen.
Rakenteet mihin harjoitusttö perustuu ovat:

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
Nämä tiedot ovat myös säilytetty:

    std::unordered_map<PlaceID, std::shared_ptr<Place>> placeById_;

    std::unordered_map<AreaID, std::shared_ptr<Area>> areaById_;

    std::unordered_map<WayID, std::shared_ptr<Way>> wayById_;

    std::unordered_map<Coord, std::shared_ptr<Crossroad>, CoordHash> crossByHash_;

Suurimassa osassa on avaimena id, mutta nodejen avaimena toimii kordinaattit käyttäen valmiiksi määriteltyä CoordHash.
Sen lisäksi olen toteuttaannut muita funktioita, joihin kuuluu

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


