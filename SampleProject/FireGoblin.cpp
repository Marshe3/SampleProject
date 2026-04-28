#include "FireGoblin.h"

FireGoblin::FireGoblin(const std::string& name,int str, int dex, int vit, int eng, int expReward, int lv)
    : Monster(name, str, dex, vit, eng, expReward, lv)
{}

int FireGoblin::Attack() const
{
    return (int)(attackDamage * 1.5f);
}

std::unique_ptr<Item> FireGoblin::Drop() const
{
    int roll = rand() % 2;
    if (roll == 0) return std::make_unique<Item>("Fire Staff", ItemType::Weapon);
    else return std::make_unique<Item>("Flame Crystal", ItemType::Consumeable);
}