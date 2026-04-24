#pragma once
#include <string>
#include "Monster.h"
#include "Player.h"

void clearScreen();
std::string makeBar(int current, int maxVal, int width, const std::string& color);

class Battle
{
private:
    Player& player;
    Monster& monster;
    std::string combatMessage;
    
public:
    Battle(Player& player, Monster& monster);
    bool Run();
    
    
};
