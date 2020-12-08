#ifndef ROBOTS_CONSOLE_VIEW_H
#define ROBOTS_CONSOLE_VIEW_H

#include <string>
#include "IGameView.h"
#include "Game.h"
#include "Texture.h"
#include "Map.h"

class ConsoleView : public IGameView {
public:
    ConsoleView(const std::string& map_file, int cnt_collectors);
    ~ConsoleView() override;

    void run() override;

private:
    Game* game;

    const std::string colorBlack = "\x1B[30m";
    const std::string colorRed = "\x1B[31m";
    const std::string colorGreen = "\x1B[32m";
    const std::string colorYellow = "\x1B[33m";
    const std::string colorBlue = "\x1B[34m";
    const std::string colorMagenta = "\x1B[35m";
    const std::string colorCyan = "\x1B[36m";
    const std::string colorWhite = "\x1B[37m";
    const std::string colorGrey = "\x1B[30;1m";
    const std::string colorDarkGrey = "\x1B[38;5;238m";
    const std::string colorDefault = "\x1B[0m";

    const int textureSize = 2;
    Texture* T_Unknown;
    Texture* T_Collector;
    Texture* T_Sapper;
    Texture* T_Apple;
    Texture* T_Bomb;
    Texture* T_Rock;
    Texture* T_Empty;

    void renderMap();
    std::pair<int, int> getConsoleSize();
    Texture* getTextureFromMap(MapElement elem);
    void putTextureInBuffer(std::vector<std::vector<std::string>>& buffer, Texture* texture, std::pair<int, int> top_left);
};

#endif
