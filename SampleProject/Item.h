#pragma once
#include <string>

enum class ItemType { Weapon, Armor, Consumeable };

class Item
{
public:
    std::string name;
    ItemType type;
    
    
    Item(const std::string &name, const ItemType type) : name(name), type(type) {}
    virtual ~Item();
};
