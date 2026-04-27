#include "Monster.h"
#include <iostream>
using namespace std;

Monster::Monster (const string& name, int str, int dex, int vit, int eng, int expReward, int lv) 
: Character(str, dex, vit, eng,  lv), name(name), expReward(expReward)
{
    std::cout << "[몬스터 등장!] HP :" << hp << " / ATK: " << attackDamage << "\n";
}


