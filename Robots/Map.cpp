#include "Map.h"

Map::Map(const std::string &map_file) {
    std::ifstream file(map_file);
    if (file.is_open()) {
        int rows = 0, cols = 0;
        file >> rows >> cols;
        file.get();
        if (rows < 1000 || cols < 1000) throw std::exception();
        for (int r = 0; r < rows; r++) {
            std::string row;
            getline(file, row);
            while ('\n' == row.back() || '\r' == row.back()) row.pop_back();
            if (row.length() != cols) throw std::exception();
            for (int c = 0; c < cols; c++) {
                switch(row[c]) {
                    case 'A':
                        addElement(r, c, MapElement::APPLE);
                        break;
                    case 'B':
                        addElement(r, c, MapElement::BOMB);
                        break;
                    case 'R':
                        addElement(r, c, MapElement::ROCK);
                        break;
                    default:
                        addElement(r, c, MapElement::EMPTY);
                        break;
                }
            }
        }
        file.close();
    }
}

MapElement Map::getElement(int r, int c) const {
    if (containsLocation(r, c)) return data.at(std::make_pair(r, c));
    else return MapElement::ROCK;
}

void Map::addElement(int r, int c, MapElement elem) {
    if (data.find(std::make_pair(r, c)) == data.end()) {
        data.insert(std::make_pair(std::make_pair(r, c), elem));
    }
    else {
        data[std::make_pair(r, c)] = elem;
    }
}

bool Map::containsLocation(int r, int c) const {
    return data.find(std::make_pair(r,c)) != data.end();
}

void Map::mergeMap(const Map &map) {
    data.insert(map.data.begin(), map.data.end());
}

const std::map<std::pair<int, int>, MapElement> & Map::getMap() const{
    return data;
}