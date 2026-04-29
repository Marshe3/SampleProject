#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Item.h"
#include <memory>

class Mercenary; // 전방 선언

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
    std::vector<Item> inventory;
    
public:
    Player(const std::string& name, const std::string& characterClass, bool isHardcore);
    
protected:
    // 자식 클래스(바바리안, 소서리스 등) 이 스탯을 직접 지정할떄 사용되는 생성자
    Player(const std::string& name, const std::string& characterClass, bool isHardcore
        , int str, int dex, int vit, int eng);
    
   public:
    // Getters
    std::string GetName() const { return name; }
    std::string GetCharacterClass() const { return characterClass; }
    bool GetIsHardcore() const { return isHardcore; }
    int GetExp() const { return exp; }
    int GetExpToNextLevel() const { return expToNextLevel; }

    std::vector<Item>& GetInventory() { return inventory; }
    
    // 플레이어-> 용병 참조
    std::shared_ptr<Mercenary> companion;
    
    // 기능(함수)
    
    
    void GainExp(int amount);
    void LevelUp();
    virtual std::string GetAttackMessage()const { return ""; }
    void PreviewCritical() const;

    int CriticalAttack() const;
    
    void PrintLevel()const;
    
    void Loot(Item item); // Battle.cpp expects this
    void Loot(std::unique_ptr<Item> item) ; // Original one in Player.cpp
    void PrintInventory() const;
};
