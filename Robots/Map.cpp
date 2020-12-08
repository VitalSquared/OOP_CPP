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
        int center_r = rows / 2, center_c = cols / 2;
        for (int r = 0; r < rows; r++) {
            std::getline(file, row);
            while ('\n' == row.back() || '\r' == row.back()) row.pop_back();
            if (row.length() != cols) throw std::exception();
            for (int c = 0; c < cols; c++) {
                switch(row[c]) {
                    case 'A':
                        addElement(r - center_r, c - center_c, MapElement::APPLE);
                        break;
                    case 'B':
                        addElement(r - center_r, c - center_c, MapElement::BOMB);
                        break;
                    case 'R':
                        addElement(r - center_r, c - center_c, MapElement::ROCK);
                        break;
                    default:
                        addElement(r - center_r, c - center_c, MapElement::EMPTY);
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
    _data.clear();
}

MapElement Map::getElement(int r, int c) const {
    if (containsLocation(r, c)) return _data[Cantor_PairToNumber(std::make_pair(r, c))];
    else return MapElement::ROCK;
}

MapElement Map::getElement(std::pair<int, int> pos) const {
    return getElement(pos.first, pos.second);
}

bool Map::containsLocation(int r, int c) const {
    int idx = Cantor_PairToNumber(std::make_pair(r, c));
    if (idx >= _data.size()) return false;
    if (_data[idx] == MapElement::UNKNOWN) return false;
    return true;
}

void Map::addElement(int r, int c, MapElement elem) {
    int idx = Cantor_PairToNumber(std::make_pair(r, c));
    if (idx < _data.size()) _data[idx] = elem;
    else {
        _data.resize(idx + 1);
        _data[idx] = elem;
    }
}

void Map::mergeMap(const Map &map) {
    for (int k = 0; k < map._data.size(); k++) {
        if (map._data[k] != MapElement::UNKNOWN) {
            std::pair<int, int> idx = Cantor_NumberToPair(k);
            addElement(idx.first, idx.second, map._data[k]);
        }
    }
}

const std::vector<MapElement>& Map::_getMap() const {
    return _data;
}