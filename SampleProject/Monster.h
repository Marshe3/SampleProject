#pragma once
#include <memory>
#include "Item.h"
#include "Character.h"
#include <string>
class Monster : public Character
{
private:
    std::string name;
    int expReward;

public:
    Monster(const std::string& name,int str, int dex, int vit, int eng, int expReward, int lv = 1);
    virtual ~Monster();
    std::string GetName() const { return name; }
    int GetExpReward() const { return expReward; }
    
    
    
    virtual std::string GetAttackMessage() const { return ""; }
    virtual std::unique_ptr<Item> Drop() const; // 몬스터 처치 시 아이템이 드롭
};
