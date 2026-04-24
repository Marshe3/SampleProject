#pragma once
using namespace std;

class Monster
{
private:
    int hp, maxHp;
    int attackDamage;

public:
    Monster(int initHp, int atk);
    ~Monster();


    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    bool isAlive() const { return hp > 0; }
    void TakeDamage(int damage);
    int Attack() const { return attackDamage; }
};
