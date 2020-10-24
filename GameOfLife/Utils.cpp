#include "Utils.h"

vector<string> StringUtils::split(const string &str, char ch) {
    vector<string> v;
    size_t pos = str.find(ch);
    size_t initialPos = 0;
    string substr;
    while (pos != string::npos) {
        substr = str.substr(initialPos, pos - initialPos);
        if (!substr.empty()) v.push_back(substr);
        initialPos = pos + 1;
        pos = str.find(ch, initialPos);
    }
    substr = str.substr(initialPos, min(pos, str.size()) - initialPos + 1);
    if (!substr.empty()) v.push_back(substr);
    return v;
}

string & StringUtils::ltrim(string &str, const string &chars) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

string & StringUtils::rtrim(std::string &str, const string &chars) {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string & StringUtils::trim(std::string &str, const string &chars) {
    return ltrim(rtrim(str, chars), chars);
}