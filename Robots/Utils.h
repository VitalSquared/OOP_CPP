#ifndef ROBOTS_UTILS_H
#define ROBOTS_UTILS_H

#include <set>
#include <vector>
#include <string>
#include "Map.h"
#include "IRobot.h"

int random(int max);
void delay(size_t ms);
void generateMap(int w, int h, std::ofstream& sv_file);

std::pair<int, int> operator+(std::pair<int, int> p1, std::pair<int, int> p2);
std::pair<int, int> operator-(std::pair<int, int> p1, std::pair<int, int> p2);

std::vector<std::string> splitString(const std::string& str, char ch);
bool fileExists(const std::string& file_name);

template <typename Container, typename Elem>
bool containerContains(const Container& container, Elem elem) {
    return container.find(elem) != container.end();
}
template <typename Container>
void containerRemove(Container& container, int idx) {
    if (0 <= idx && idx < container.size()) container.erase(container.begin() + idx);
}

std::vector<std::pair<int, int>> findSuitablePos(int count, const std::map<std::pair<int, int>, MapElement>& data, const std::set<MapElement>& allowed);
std::vector<std::pair<int, int>> findSuitablePos(int count, const std::vector<MapElement>& data, const std::set<MapElement>& allowed);
std::vector<std::pair<int, int>> buildPath(std::pair<int, int> start, std::pair<int, int> end, const Map& scannedMap,
                                           const std::set<MapElement>& canWalkOn, const std::set<std::pair<int, int>>& unreachable);
std::vector<std::pair<int, int>> getAdjacentCoords(int pos_r, int pos_c);
std::vector<std::pair<int, int>> getAdjacentCoords(std::pair<int, int> pos);
double calcDistance(std::pair<int, int> point1, std::pair<int, int> point2);

bool convertStringToInt(const std::string& str, int& out);
Direction convertStringToDirection(const std::string &str);
Direction convertDeltaToDirection(std::pair<int, int> _pair);
std::pair<int, int> convertDirectionToDelta(Direction dir);

int Cantor_PairToNumber(std::pair<int, int> _pair);
std::pair<int, int> Cantor_NumberToPair(int num);

#endif
