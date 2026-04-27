#include "Player.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Player::Player(const string& name, const string& characterClass, bool isHardcore)
    : Character(50, 50, 50, 50, 1),
    // 단순 값 세팅 초기화
    name(name), characterClass(characterClass), isHardcore(isHardcore),
    exp(0), expToNextLevel(100){}
    
Player::Player(const string& name, const string& characterClass, bool isHardcore
    , int str, int dex, int vit, int eng)
: Character(str, dex, vit, eng, 1), exp(0), expToNextLevel(100) {}

void Player::LevelUp()
{
    level++;
}

void Player::PreviewCritical() const
{
    float preview = attackDamage * 2;
    cout << "크리티컬 예상 데미지: " << preview << "\n";
}

void Player:: PrintLevel() const
{
    cout << "현재레벨 : " << level << "\n";
}

int Player::CriticalAttack() const
{
    return (int)(attackDamage * 2);
}

void Player::GainExp(int amount)
{
    exp += amount;
    if (exp >= expToNextLevel)
    {
        exp-= expToNextLevel;
        level++;
        expToNextLevel = level * 100;
        cout << "[레벨 업!]" << level << "\n";
    }
}
void Player::Loot(int count)
{
    // count개 아이템을 vector에 추가
    for (int i = 0; i <count; i++)
    {
        // 랜덤 숫자 1개씩 인벤토리에 벡터에 넣음
        inventory.push_back(rand() % 4 + 1);
        for (int j = 0; j <inventory.size(); j++)
        {
            string itemName;
            if (inventory[i] == 1) itemName = "Gold";
            else if(inventory[i] == 2) itemName = "Healing Potion";
            else if (inventory[i] == 3) itemName = "Weapon";
            else if (inventory[i] == 4) itemName = "Armor";
            else itemName = "Empty Slot";


            cout << " > Slot " << i <<  " [" << itemName << "]\n";
        }
        
    }
}