#ifndef ROBOTS_UTILS_H
#define ROBOTS_UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

enum class ErrorType { OTHER, INVALID_ARGS, NO_FILE, CANT_CREATE_FILE, WH1000,  };

vector<string> splitString(const string& str, char ch = ' ');

void generateMap(int w, int h, ofstream& sv_file);
void printError(ErrorType err);
void delay(int ms);
int random(int max);

#endif
