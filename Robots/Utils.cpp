#include "Utils.h"
#include <chrono>
#include <thread>

using namespace std;

string& ltrimString(string &str, const string &chars) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

string& rtrimString(std::string &str, const string &chars) {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string& trimString(std::string &str, const string &chars) {
    return ltrimString(rtrimString(str, chars), chars);
}

vector<string> splitString(const string &str, char ch) {
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

void generateMap(int w, int h, ofstream& sv_file) {
    sv_file << h << " " << w << endl;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            int type = random(10);

            if (type == 2) sv_file << "B";
            else if (type == 5) sv_file << "R";
            else if (type == 8) sv_file << "A";
            else sv_file << " ";
        }
        sv_file << endl;
    }
}

void printError(ErrorType err) {
    switch(err) {
        case ErrorType::INVALID_ARGS:
            cout << R"(Invalid arguments or no arguments provided.)" << endl;
            break;
        case ErrorType::NO_FILE:
            cout << "File doesn't exist. Exiting..." << endl;
            break;
        case ErrorType::CANT_CREATE_FILE:
            cout << "Can't create file. Exiting..." << endl;
            break;
        case ErrorType::WH1000:
            cout << "Width and Height must be at least 1000. Exiting..." << endl;
            break;
        default:
            cout << "Error. Exiting..." << endl;
    }
    cout << "Press ENTER to continue." << endl;
    cin.get();
}

void delay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}


int random(int max) {
    srand(time(nullptr));
    return rand() % max;
}