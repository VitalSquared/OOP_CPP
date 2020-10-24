#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

using namespace std;

class StringUtils {
public:
    static vector<string> split(const string& str, char ch);
    static string& ltrim(string& str, const string& chars = "\t\n\v\f\r ");
    static string& rtrim(string& str, const string& chars = "\t\n\v\f\r ");
    static string& trim(string& str, const string& chars = "\t\n\v\f\r ");
};

#endif
