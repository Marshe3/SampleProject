#include "Mercenary.h"
#include <memory>
#include <iostream>

using namespace std;
Mercenary::Mercenary(const string& name, int atk, shared_ptr<Player> owner)
    : name(name), attackDamage(atk), owner(owner)
{
    cout << "[용병 고용]" << name << "가 합류했습니다.";
    
}

Mercenary::~Mercenary()
{
    cout << "[용병 소멸]" << name << "\n";
}