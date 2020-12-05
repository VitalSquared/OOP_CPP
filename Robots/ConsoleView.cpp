#include <iostream>
#include <windows.h>
#include "Utils.h"
#include "ConsoleView.h"

ConsoleView::ConsoleView(const std::string& map_file, int cnt_collectors) {
    game = new Game(map_file, cnt_collectors);

    T_Unknown = new Texture(textureSize, colorDarkGrey, "????");
    T_Collector = new Texture(textureSize, colorGreen, "Robo");
    T_Sapper = new Texture(textureSize, colorCyan, "Sapp");
    T_Apple = new Texture(textureSize, colorRed, "/\\oo");
    T_Bomb = new Texture(textureSize, colorMagenta, "()()");
    T_Rock = new Texture(textureSize, colorGrey, "\\}{\\");
    T_Empty = new Texture(textureSize, colorWhite, "    ");

    renderMap();
}

ConsoleView::~ConsoleView() {
    delete game;
    game = nullptr;

    delete T_Unknown;
    T_Unknown = nullptr;

    delete T_Collector;
    T_Collector = nullptr;

    delete T_Sapper;
    T_Sapper = nullptr;

    delete T_Apple;
    T_Apple = nullptr;

    delete T_Bomb;
    T_Bomb = nullptr;

    delete T_Rock;
    T_Rock = nullptr;

    delete T_Empty;
    T_Empty = nullptr;
}

void ConsoleView::run() {
    std::string cmd;
    do {
        std::getline(std::cin, cmd);
        if (cmd == "exit") break;
        if (cmd.empty()) {
            renderMap();
            continue;
        }
        if (game->parseCommand(cmd)) {
            while(game->step()) {
                renderMap();
                delay(500);
            }
        }
        else std::cout << "Invalid command or argument(s).\n";
    } while(true);
}

void ConsoleView::renderMap() {
    system("cls");

    int width, height;
    width = getConsoleSize().first;
    height = getConsoleSize().second;

    const std::vector<IRobot*> robots = game->getRobots();
    const IRobot* curCollector = game->getActiveCollector();

    if (curCollector == nullptr) {
        std::cout << "No map to draw. Looks like all collectors are gone..." << std::endl;
        return;
    }

    int padding_top = 1 * (textureSize + 1), padding_bottom = 2 * (textureSize + 1),
            padding_left = 1 * (textureSize + 1), padding_right = 2 * (textureSize + 1);

    int map_width = (width - (padding_left + padding_right)) / (textureSize + 1),
        map_height = (height - (padding_top + padding_bottom)) / (textureSize + 1);
    if (map_width <= 0 || map_height <= 0) {
        std::cout << "Impossible to draw map. Invalid map size. Try to increase Console Window size" << std::endl;
        return;
    }

    int center_r = curCollector->getPosition().first, center_c = curCollector->getPosition().second;
    int top_left_r = center_r - map_height / 2, top_left_c = center_c - map_width / 2;

    std::vector<std::vector<std::string>> buffer(map_height * textureSize, std::vector<std::string>(map_width * textureSize));

    for (int r = 0; r < map_height; r++) {
        for (int c = 0; c < map_width; c++) {
            Texture* texture;
            if (curCollector->getLocalMap().containsLocation(r + top_left_r, c + top_left_c)) {
                MapElement elem = curCollector->getLocalMap().getElement(r + top_left_r, c + top_left_c);
                texture = getTextureFromMap(elem);
            }
            else texture = T_Unknown;
            putTextureInBuffer(buffer, texture, std::make_pair(textureSize * r, textureSize * c));
        }
    }

    int apples = 0;

    for (auto* robot : robots) {
        Texture* texture;
        std::string id = "0" + std::to_string(robot->getRobotID().second);

        switch(robot->getRobotID().first) {
            case RobotType::COLLECTOR:
                texture = new Texture(textureSize, colorGreen, "Rb" + id.substr(id.size() - 2));
                apples += robot->getInvestment();
                break;
            case RobotType::SAPPER:
                texture = new Texture(textureSize, colorCyan, "Sp" + id.substr(id.size() - 2));
                break;
        }

        int pos_r = robot->getPosition().first, pos_c = robot->getPosition().second;
        putTextureInBuffer(buffer, texture, std::make_pair(textureSize * (pos_r - top_left_r), textureSize * (pos_c - top_left_c)));

        delete texture;
        texture = nullptr;
    }

    for (int r = 0; r < padding_top; r++) std::cout << std::endl;
    std::string output;
    int i = 0;
    for (const auto& row : buffer) {
        int j = 0;
        output += std::string(padding_left, ' ');
        for (const auto& col : row) {
            output += colorDefault + col + colorDarkGrey + (j == textureSize - 1 ? "|" : "");
            j++;
            if (j >= textureSize) j = 0;
        }
        output += "\n";
        if (i == textureSize - 1) {
            output += std::string(padding_left, ' ');
            output += colorDarkGrey + std::string(row.size() * (textureSize + 1) / textureSize, '-');
            output += "\n";
        }
        i++;
        if (i >= textureSize) i = 0;
    }

    std::cout << output + colorDefault << std::endl;
    std::cout << "\tApples collected: " << apples << std::endl;
    std::cout << std::endl;
}

std::pair<int, int> ConsoleView::getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width, height;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return std::make_pair(width > 100 ? width : 100, height > 25 ? height : 25);
}

Texture * ConsoleView::getTextureFromMap(MapElement elem) {
    Texture* texture;
    switch(elem) {
        case MapElement::EMPTY: texture = T_Empty; break;
        case MapElement::BOMB: texture = T_Bomb; break;
        case MapElement::APPLE: texture = T_Apple; break;
        case MapElement::ROCK: texture = T_Rock; break;
    }
    return texture;
}

void ConsoleView::putTextureInBuffer(std::vector<std::vector<std::string>>& buffer, Texture *texture, std::pair<int, int> top_left) {
    bool fail = false;
    for (int tr = 0; tr < texture->getSize(); tr++) {
        for (int tc = 0; tc < texture->getSize(); tc++) {
            int r = top_left.first + tr, c = top_left.second + tc;
            if (r < 0 || r >= buffer.size() || c < 0 || c >= buffer[r].size()) {
                fail = true;
                break;
            }
            buffer[r][c] = texture->getPixel(tr, tc);
        }
        if (fail) break;
    }
}