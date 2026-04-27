#pragma once
#include "Player.h"
#include <string>

class Barbarian: public Player
{
public:
    Barbarian(const std::string& name, bool isHardcore);
    
    int Attack() const override;
    std::string GetAttackMessage() const override { return "[Bash!]"; }
    
};
