#ifndef ROBOTS_MAP_H
#define ROBOTS_MAP_H

#include <map>
#include <string>

enum class MapElement { UNKNOWN, EMPTY, BOMB, ROCK, APPLE };

class Map {
public:
    Map() = default;
    Map(const std::string& map_file);
    ~Map();

    MapElement getElement(int r, int c) const;
    MapElement getElement(std::pair<int, int> pos) const;
    bool containsLocation(int r, int c) const;

    void addElement(int r, int c, MapElement elem);
    void mergeMap(const Map& map);

    const std::vector<MapElement>& _getMap() const;

private:
    std::vector<MapElement> _data;
};

#endif
