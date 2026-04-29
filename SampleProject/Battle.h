#pragma once
#include <string>
#include <vector>
#include "Monster.h"
#include "Player.h"

void clearScreen();
std::string makeBar(int current, int maxVal, int width, const std::string& color);

class Battle
{
private:
    Player& player;
    std::vector<Monster*>& monsters;
    std::shared_ptr<Mercenary> mercenary; // 없을 경우 nullptr
    std::string combatMessage;

public:
    Battle(Player& player, std::vector<Monster*>& monsters, std::shared_ptr<Mercenary> mercenary = nullptr);
    bool Run();
};
