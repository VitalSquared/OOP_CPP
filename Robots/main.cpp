#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "optionparser.h"
#include "GameView.h"
#include "Command.h"
#include "Field.h"

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
    srand(time(0));
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

void printError(int err) {
    switch(err) {
        case 0:
            cout << R"(Invalid options. Use "-generate w h file_name" to generate map or "file_name" to load it)" << endl;
            break;
        case 1:
            cout << "File doesn't exist. Exiting..." << endl;
            break;
        case 2:
            cout << "Can't create file. Exiting..." << endl;
            break;
        case 3:
            cout << "Width and Height must be at least 1000. Exiting..." << endl;
            break;
        default:
            cout << "Error. Exiting..." << endl;
    }
    cout << "Press ENTER to continue." << endl;
    cin.get();
}

int main(int argc, char* argv[]) {
    argc -= (argc>0); //  \/
    argv += (argc>0); //   skip program name argv[0] if present

    ifstream ld_file;

    if (argc >= 1) {
        if (!strcmp("-generate", argv[0])) {
            if (argc != 4) {
                printError(0);
                return 0;
            }
            int w, h;
            try {
                w = stoi(argv[1]);
                h = stoi(argv[2]);
            }
            catch (exception&) {
                printError(0);
                return 0;
            }
            if (w < 1000 || h < 1000) {
                printError(3);
                return 0;
            }
            string fl_name(argv[3]);
            fl_name = trimString(fl_name, "\"");
            ofstream sv_file(fl_name);
            if (!sv_file.is_open()) {
                printError(2);
                return 0;
            }
            cout << "Generating..." << endl;
            generateMap(w, h, sv_file);
            sv_file.close();
            cout << "Generation completed. Exiting..." << endl;
            cout << "Press ENTER to continue." << endl;
            cin.get();
            return 0;
        }
        else {
            if (argc > 1) {
                printError(0);
                return 0;
            }
            string fl_name(argv[0]);
            fl_name = trimString(fl_name, "\"");
            ld_file.open(fl_name);
            if (!ld_file.is_open()) {
                printError(1);
                return 0;
            }
        }
    }
    else {
        cout << "No arguments provided. Exiting..." << endl;
        cout << "Press any button to continue." << endl;
        cin.get();
        return 0;
    }

    try {
        Field field(ld_file);
        ld_file.close();

        Collector collector(field);
        GameView gameView(&field, &collector);
        gameView.renderField();

        string cmd;
        getline(cin, cmd);
        while (cmd != "exit") {
            if (!collector.getDeadState()) {
                if (cmd == "MOVE U") {
                    collector.move(Direction::UP, field);
                } else if (cmd == "MOVE D") {
                    collector.move(Direction::DOWN, field);
                } else if (cmd == "MOVE L") {
                    collector.move(Direction::LEFT, field);
                } else if (cmd == "MOVE R") {
                    collector.move(Direction::RIGHT, field);
                } else if (cmd == "GRAB") {
                    collector.grab(field);
                } else if (cmd == "SCAN") {
                    collector.scan();
                }
                gameView.renderField();
            }
            getline(cin, cmd);
        }
    }
    catch (exception&) {
        if (ld_file.is_open()) ld_file.close();
        printError(-1);
    }
    return 0;
}
