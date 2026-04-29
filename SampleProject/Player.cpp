#include "Player.h"
#include <iostream>
#include <iomanip>
#include <string>

#include "Item.h"
using namespace std;

Player::Player(const string& name, const string& characterClass, bool isHardcore)
    : Character(50, 50, 50, 50, 1),
    // 단순 값 세팅 초기화
    name(name), characterClass(characterClass), isHardcore(isHardcore),
    exp(0), expToNextLevel(100)
{
    inventory.reserve(6);  // 재할당에 따른 복사 (Reallocation)을 방지하기 위해서 미리 capacity 확보
}    



Player::Player(const string& name, const string& characterClass, bool isHardcore
    , int str, int dex, int vit, int eng)
: Character(str, dex, vit, eng, 1), exp(0), expToNextLevel(100)
{
    inventory.reserve(6);
}

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
    for (int i = 0; i < count; ++i) {
        Loot(make_unique<Item>("Gold Coin", ItemType::Consumeable));
        cout << "[인벤토리] size = " << inventory.size() << " capacity = " << inventory.capacity() << "\n";
    }
}

void Player::Loot(unique_ptr<Item> item)
{
    cout << "[획득]" << item->name << "\n";
    inventory.push_back(*item);
    
}

// Range-based for 문 | const auto&
void Player::PrintInventory() const {
    cout << "||" << left << setw(46) << " Inventory" << "\n";
    int i = 1;
    for (const auto& item : inventory)
    {
        string typeStr;
        if (item.type == ItemType::Weapon) typeStr = "Weapon";
        else if (item.type == ItemType::Armor) typeStr = "Armor";
        else typeStr = "Consumable";

        cout << " > Slot " << i++ << " [" << item.name << "] (" << typeStr << ")\n";
    }
    
}

bool Player::UseItem(const string& itemName)
{
    for (auto it = inventory.begin(); it != inventory.end(); ++it)
    {
        if (it->name == itemName)
        {
            if (it->type == ItemType::Consumeable)
            {
                Heal(maxHp); // 전체회복
            }
            it = inventory.erase(it); // erase 후 유효한 iterator 반환
            cout << "[인벤토리] 아이템 사용 후 size = " << inventory.size() << " capacity = " << inventory.capacity() << "\n"; 
            return true;
        }
    }
    return false;
} 
