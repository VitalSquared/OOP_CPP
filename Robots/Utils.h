#ifndef ROBOTS_UTILS_H
#define ROBOTS_UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

enum class ErrorType { OTHER, INVALID_ARGS, NO_FILE, CANT_CREATE_FILE, WH1000,  };

string& ltrimString(string &str, const string &chars);
string& rtrimString(std::string &str, const string &chars);
string& trimString(std::string &str, const string &chars);

void generateMap(int w, int h, ofstream& sv_file);
void printError(ErrorType err);
void delay(int ms);

#endif
