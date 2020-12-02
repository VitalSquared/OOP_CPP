#ifndef ROBOTS_MAP_H
#define ROBOTS_MAP_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>

enum class MapElement { EMPTY, BOMB, ROCK, APPLE };

class Map {
public:
    Map() = default;
    Map(const std::string& map_file);
    ~Map() = default;

    MapElement getElement(int r, int c) const;
    void addElement(int r, int c, MapElement elem, bool overrideValue = true);
    bool containsLocation(int r, int c) const;
    void mergeMap(const Map& map);

    const std::map<std::pair<int, int>, MapElement>& getMap() const;

private:
    std::map<std::pair<int, int>, MapElement> data;
};

#endif
