#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Map.h"

Map::Map(const std::string &map_file) {
    std::ifstream file(map_file);
    std::string row;

    if (file.is_open()) {
        std::cout << "0%\r";
        int rows = 0, cols = 0;
        file >> rows >> cols;
        file.get();
        if (rows < 1000 || cols < 1000) throw std::exception();
        for (int r = 0; r < rows; r++) {
            std::getline(file, row);
            while ('\n' == row.back() || '\r' == row.back()) row.pop_back();
            if (row.length() != cols) throw std::exception();
            for (int c = 0; c < cols; c++) {
                switch(row[c]) {
                    case 'A':
                        addElement(r, c, MapElement::APPLE, false);
                        break;
                    case 'B':
                        addElement(r, c, MapElement::BOMB, false);
                        break;
                    case 'R':
                        addElement(r, c, MapElement::ROCK, false);
                        break;
                    default:
                        addElement(r, c, MapElement::EMPTY, false);
                        break;
                }
            }
            int percent = (int)(100.0 * r / rows);
            std::cout << std::string(percent, '.') << percent << "%" << "\r";
        }
        file.close();
        std::cout << std::string(100, '.') << "100%" << std::endl;
    }
}

Map::~Map() {
    data.clear();
}

MapElement Map::getElement(int r, int c) const {
    if (containsLocation(r, c)) return data.at(std::make_pair(r, c));
    else return MapElement::ROCK;
}

MapElement Map::getElement(std::pair<int, int> pos) const {
    return getElement(pos.first, pos.second);
}

bool Map::containsLocation(int r, int c) const {
    return containerContains(data, std::make_pair(r,c));
}

void Map::addElement(int r, int c, MapElement elem, bool overrideValue) {
    if (!overrideValue || !containerContains(data, std::make_pair(r, c))) {
        data.insert(std::make_pair(std::make_pair(r, c), elem));
    }
    else {
        data[std::make_pair(r, c)] = elem;
    }
}

void Map::mergeMap(const Map &map) {
    for (auto elem : map.getMap()) {
        addElement(elem.first.first, elem.first.second, elem.second);
    }
}

const std::map<std::pair<int, int>, MapElement> & Map::getMap() const{
    return data;
}