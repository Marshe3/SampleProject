#pragma once
#include <memory>
#include <string>

#include "Player.h"

class Mercenary
{
public:
    std::string name;
    int attackDamage;
    std::shared_ptr<Player> owner;
    
    Mercenary(const std::string& name, int atk, std::shared_ptr<Player> owner);
    ~Mercenary();
    
    int Attack() const { return attackDamage; }
    bool IsOwnerAlive() const { return owner != nullptr; } // 주인이 살아 있는지 확인
    
};
