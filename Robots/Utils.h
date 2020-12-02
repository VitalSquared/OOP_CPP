#ifndef ROBOTS_UTILS_H
#define ROBOTS_UTILS_H

#include <set>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include "Map.h"
#include "IRobot.h"

int random(int max);
void delay(size_t ms);

std::vector<std::string> splitString(const std::string& str, char ch);

template <typename Container, typename Elem>
bool containerContains(const Container& container, Elem elem) {
    return container.find(elem) != container.end();
}

std::pair<int, int> findSuitablePos(const std::map<std::pair<int, int>, MapElement>& data, const std::set<MapElement>& allowed);
std::vector<std::pair<int, int>> buildPath(int rs, int cs, int rf, int cf, const Map& scannedMap,
                                           const std::set<MapElement>& canWalkOn, const std::set<std::pair<int, int>>& unreachable);
Direction calcDirection(std::pair<int, int> start, std::pair<int, int> end);

std::vector<std::pair<int, int>> getAdjacentCoords(int pos_r, int pos_c);
double calcDistance(std::pair<int, int> point1, std::pair<int, int> point2);

void generateMap(int w, int h, std::ofstream& sv_file);
bool fileExists(const std::string& file_name);

bool convertStringToInt(const std::string& str, int& out);
Direction convertStringToDirection(const std::string &str);
Direction convertPairToDirection(std::pair<int, int> _pair);
std::pair<int, int> convertDirectionToDelta(Direction dir);

#endif
