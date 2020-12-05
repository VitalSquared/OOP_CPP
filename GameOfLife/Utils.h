#ifndef GAMEOFLIFE_UTILS_H
#define GAMEOFLIFE_UTILS_H

#include <vector>
#include <string>

using namespace std;

vector<string> splitString(const string &str, char ch);
string& ltrimString(string &str, const string &chars);
string& rtrimString(std::string &str, const string &chars);
string& trimString(std::string &str, const string &chars);

int pairToIndex(int r, int c, int cols);

#endif
