#include "ConsoleView.h"

ConsoleView::ConsoleView(const std::string& map_file) {
    game = new Game(map_file);

    T_Unknown = new Texture(textureSize, colorDarkGrey, "????");
    T_Collector = new Texture(textureSize, colorGreen, "Robo");
    T_Sapper = new Texture(textureSize, colorCyan, "Sapp");
    T_Apple = new Texture(textureSize, colorRed, "|\\oo");
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

    std::vector<const IRobot*> robots = game->getRobots();
    const IRobot* curCollector = nullptr;

    for (auto* robot : robots) {
        if (robot->getRobotType() == RobotType::COLLECTOR) {
            curCollector = robot;
            break;
        }
    }

    if (curCollector == nullptr) return;

    int map_width = (width - 5) / textureSize / 2, map_height = (height - 5) / textureSize / 2;
    int center_r = curCollector->getPosition().first, center_c = curCollector->getPosition().second;
    int top_left_r = center_r - map_height / textureSize, top_left_c = center_c - map_width / textureSize;

    if (map_width <= 0 || map_height <= 0) return;

    std::vector<std::vector<std::string>> buffer(map_height * textureSize, std::vector<std::string>(map_width * textureSize));

    for (int r = 0; r < map_height; r++) {
        for (int c = 0; c < map_width; c++) {
            Texture* texture;
            if (curCollector->getLocalMap().containsLocation(r + top_left_r, c + top_left_c)) {
                MapElement elem = curCollector->getLocalMap().getElement(r + top_left_r, c + top_left_c);
                texture = getTextureFromMap(elem);
            }
            else {
                texture = T_Unknown;
            }
            putTextureInBuffer(buffer, texture,std::make_pair(textureSize * r, textureSize * c));
        }
    }

    putTextureInBuffer(buffer, T_Collector, std::make_pair(textureSize * (center_r - top_left_r),textureSize * (center_c - top_left_c)));

    std::string output;
    int i = 0;
    for (const auto& row : buffer) {
        int j = 0;
        for (const auto& col : row) {
            output += colorDefault + col + colorDarkGrey + (j == textureSize - 1 ? "|" : "");
            j++;
            if (j >= textureSize) j = 0;
        }
        output += "\n";
        if (i == textureSize - 1) {
            output += colorDarkGrey + std::string(row.size() * 1.5, '-');
            output += "\n";
        }
        i++;
        if (i >= textureSize) i = 0;
    }

    std::cout << output + colorDefault << std::endl;
}

std::pair<int, int> ConsoleView::getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width, height;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return std::make_pair(width, height);
}

Texture * ConsoleView::getTextureFromMap(MapElement elem) {
    switch(elem) {
        case MapElement::EMPTY: return T_Empty;
        case MapElement::BOMB: return T_Bomb;
        case MapElement::APPLE: return T_Apple;
        case MapElement::ROCK: return T_Rock;
    }
}

void ConsoleView::putTextureInBuffer(std::vector<std::vector<std::string>>& buffer, Texture *texture, std::pair<int, int> top_left) {
    for (int tr = 0; tr < texture->getSize(); tr++) {
        for (int tc = 0; tc < texture->getSize(); tc++) {
            buffer[top_left.first + tr][top_left.second + tc] = texture->getPixel(tr, tc);
        }
    }
}