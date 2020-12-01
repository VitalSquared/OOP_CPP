#ifndef ROBOTS_UTILS_H
#define ROBOTS_UTILS_H

#include <set>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include "Map.h"

int random(int max);
void delay(size_t ms);
std::vector<std::string> splitString(const std::string& str, char ch);
std::pair<int, int> findSuitablePos(const std::map<std::pair<int, int>, MapElement>& data, const std::set<MapElement>& allowed);

#endif
