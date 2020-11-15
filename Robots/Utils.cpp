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

void generateMap(int w, int h, ofstream& sv_file) {
    sv_file << h << " " << w << endl;
    srand(time(nullptr));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            int type = rand() % 10;

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
            cout << R"(Invalid arguments or no arguments provided. Use "-generate w h file_name" to generate map or "file_name" to load it)" << endl;
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
