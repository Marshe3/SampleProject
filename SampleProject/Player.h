#pragma once
#include <string>
#include <iostream>

#include "Character.h"

class Player : public Character
{
private: 
    // Player 고유 정보
    std::string name;
    std::string characterClass;
    bool isHardcore;
    
    // 경험치 획득
    int exp, expToNextLevel;
    
    
    // 인벤토리
    int inventory[5];
    
public:
    Player(const std::string& name, const std::string& characterClass, bool isHardcore);
    
   
    // Getters
    std::string GetName() const { return name; }
    std::string GetCharacterClass() const { return characterClass; }
    bool GetIsHardcore() const { return isHardcore; }
    int GetExp() const { return exp; }
    int GetExpToNextLevel() const { return expToNextLevel; }

    int* GetInventory() { return inventory; }
    
    // 기능(함수)
    
    
    void GainExp(int amount);
    void LevelUp();

    void PreviewCritical() const;

    int CriticalAttack() const;
    
    void PrintLevel()const;
    
    
};
