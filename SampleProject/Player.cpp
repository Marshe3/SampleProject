#include "Player.h"
#include <iostream>

#include <string>
using namespace std;

Player::Player(const string& name, const string& characterClass, bool isHardcore)
// 외부입력 값 세팅 초기화
       : name(name), characterClass(characterClass), isHardcore(isHardcore), //단순 값 세팅 초기화
   strength(50), dexterity(50), vitality(50), energy(50),
   level(1),
   fireResist(0), coldResist(0), lightningResist(0), poisonResist(0)
{
    maxHp = vitality * 2; // 계산이 필요한 값 세팅 초기화
    hp = maxHp;
    maxMp = (int)energy * 1.5f;
    mp = maxMp;
    attackDamage = strength * 0.2f;
    attackSpeed = dexterity / 10.0f;
    movingSpeed = dexterity / 30.0f;
    for (int i = 0; i < 5; i++) inventory[i] = 0;
}

void Player::TakeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0) hp = 0;
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