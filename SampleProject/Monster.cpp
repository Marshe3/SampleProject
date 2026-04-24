#include "Monster.h"
#include <iostream>

Monster::Monster (int str, int dex, int vit, int eng, int expReward, int lv) 
: Character(str, dex, vit, eng,  lv), expReward(expReward)
{
    std::cout << "[몬스터 등장!] HP :" << hp << " / ATK: " << attackDamage << "\n";
}


