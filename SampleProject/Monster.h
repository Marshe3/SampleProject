#pragma once
#include "Character.h"
#include <string>
class Monster : public Character
{
private:
    std::string name;
    int expReward;

public:
    Monster(const std::string& name,int str, int dex, int vit, int eng, int expReward, int lv = 1);
    
    std::string GetName() const { return name; }
    int GetExpReward() const { return expReward; }
    
    virtual std::string GetAttackMessage() const { return ""; }
    
};
