#pragma once
#include <string>
#include <iostream>
#include <vector>
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
    std::vector<int> inventory;
    
public:
    Player(const std::string& name, const std::string& characterClass, bool isHardcore);
    
   
    // Getters
    std::string GetName() const { return name; }
    std::string GetCharacterClass() const { return characterClass; }
    bool GetIsHardcore() const { return isHardcore; }
    int GetExp() const { return exp; }
    int GetExpToNextLevel() const { return expToNextLevel; }

    std::vector<int>& GetInventory() { return inventory; }
    
    // 기능(함수)
    
    
    void GainExp(int amount);
    void LevelUp();

    void PreviewCritical() const;

    int CriticalAttack() const;
    
    void PrintLevel()const;
    
    void Loot(int count = 3); // 빈슬롯부터 count개의 아이템 획득 -> 인벤토리에 저장 + 출력
};
