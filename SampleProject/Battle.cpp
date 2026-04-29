#include "Battle.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#define NOMINMAX
#include <windows.h>

#include "Mercenary.h"
using namespace std;

#define RESET    "\033[0m"
#define BOLD     "\033[1m"
#define DIM      "\033[2m"
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE     "\033[34m"
#define MAGENTA  "\033[35m"
#define CYAN     "\033[36m"
#define GRAY     "\033[90m"
#define BRED     "\033[91m"
#define BGREEN   "\033[92m"
#define BYELLOW  "\033[93m"
#define BBLUE    "\033[94m"
#define BMAGENTA "\033[95m"
#define BCYAN    "\033[96m"
#define BWHITE   "\033[97m"
// [UI] 화면을 깨끗하게 지우는 함수
void clearScreen() {
    cout << "\033[2J\033[H\033[3J";
}

void printMonsterSprite(int currentHp, int maxHp) {
    if (currentHp > maxHp / 2) {
        // 건강한 고블린 - 날카로운 귀, 사악한 돼지 코, 철퇴와 방패로 완전 무장
        cout << BGREEN << R"(
                 ,      ,
                /(.----.)\
            |\  \/ (_) (_) \/  /|
            | \ / ^   -   ^ \ / |
            \( \   _/\_   / )/
             \_, '-/  \-' ,_/
               /   \__/   \
               \ @ /\ @ /
              __\ \\// // /__
            /`   '      '    `\
           |   (@@@)       |
           |    ||||       |
           |   _||||_      |
           \_ /      \ __/
             \_ [=||=] _/
                ||||
)" << RESET;
    }
    else {
        // 부상당한 고블린 - X 흉터, 부서진 철퇴, 깨진 방패
        cout << BYELLOW << R"(
                 ,      ,
                /(.----.)\
            |\  \/ (_) (_) \/  /|
            | \ / X   -   X \ / |
            \( \   _/\_   / )/
             \_, '-/  \-' ,_/
               /   \__/   \
               \ X  /\ X /
              __\ \\// // /__
            /`   '      '    `\
           |   (@@ )       |
           |    ||||       |
           |   _||||_      |
           \_ /      \ __/
             \_ [_/_/_] _/
                ||||
)" << RESET;
    }
}

// Call By Value 복사본 전달 -> 원본은 변경되지 않음
void PreviewCritical(float attackDamage) {
    attackDamage *= 2; // Parameter 복사본만 2배, 원본 변수는 그대로
    cout << "크리티컬 예상 데미지: " << attackDamage << "\n";
}

// [UI] HP/MP 게이지 바 문자열을 만드는 헬퍼 함수
string makeBar(int current, int maxVal, int width, const string& color) {
    if (maxVal <= 0) maxVal = 1;
    int filled = (current * width) / maxVal;
    if (filled < 0) filled = 0;
    if (filled > width) filled = width;

    string bar = color;
    for (int i = 0; i < filled; i++) bar += "#";
    bar += GRAY;
    for (int i = filled; i < width; i++) bar += ".";
    bar += RESET;
    return bar;
}



Battle::Battle(Player& player, vector<Monster*>& monsters, shared_ptr<Mercenary> mercenary) {}
    : player(player), monsters(monsters), combatMessage("[System] Battle Started!") {}


bool Battle::Run()
{
    for (Monster* monster : monsters)
    {
        if (!player.isAlive()) break;

        int action;

        cout << "\n";
        cout << BRED << "  >> ====== ENEMY ENCOUNTERED ====== <<\n" << RESET;
        printMonsterSprite(monster->GetHp(), monster->GetMaxHp());
        cout << "\n";
        cout << BGREEN << "      A wild " << BOLD << monster->GetName() << RESET
            << BGREEN << " emerges from the shadows!\n" << RESET;
        cout << "\n";
        Sleep(1500);

        while (monster->isAlive() && player.isAlive()) {
            clearScreen();

            cout << "\n";
            cout << BRED << "  >> ========== BATTLE ========== <<\n" << RESET;
            printMonsterSprite(monster->GetHp(), monster->GetMaxHp());

            cout << GRAY << "  ------------------------------------------\n" << RESET;
            cout << "   " << BGREEN << monster->GetName() << " " << RESET
                << makeBar(monster->GetHp(), monster->GetMaxHp(), 15, BGREEN)
                << "  " << BGREEN << monster->GetHp() << "/" << monster->GetMaxHp() << "\n" << RESET;
            cout << "   " << BRED << "You    " << RESET
                << makeBar(player.GetHp(), player.GetMaxHp(), 15, BRED)
                << "  " << BRED << player.GetHp() << "/" << player.GetMaxHp() << "\n" << RESET;
            cout << GRAY << "  ------------------------------------------\n" << RESET;
            cout << "\n";
            cout << "   " << BYELLOW << "[1] Attack      [2] Critical Attack\n" << RESET;
            cout << BYELLOW << "  > Action: " << RESET;
            cin >> action;

            if (action == 1) {
                monster->TakeDamage((int)player.GetAttackDamage());
                cout << "\n";
                cout << "   " << BYELLOW << ">> You strike the " << monster->GetName() << "!" << RESET
                    << RED << "  (-" << player.GetAttackDamage() << ")\n" << RESET;
                Sleep(500);
                if (mercenary && monster->isAlive())
                {
                    int mercDmg = mercenary -> Attack();
                    monster->TakeDamage((int)mercDmg);
                    combatMessage += "\n=> [" + mercenary->name +  "] attacked! (Dmg: " + to_string(mercDmg) + ")";
                }
                if (monster->isAlive()) {
                    player.TakeDamage(monster->Attack());
                    cout << "   " << BRED << ">> The " << monster->GetName() << " retaliates!" << RESET
                        << RED << "  (-" << monster->Attack() << ")\n" << RESET;
                    Sleep(900);
                }
                else {
                    cout << "   " << BGREEN << ">> " << monster->GetName() << " is slain!\n" << RESET;
                    Sleep(1300);
                }
            }
            else if (action == 2) {
                int crit = player.CriticalAttack();
                monster->TakeDamage(crit);
                cout << "\n";
                cout << "   " << BMAGENTA << ">> CRITICAL STRIKE! " << BYELLOW << "You deal massive damage!" << RESET
                    << RED << " (-" << crit << ")\n" << RESET;
                Sleep(500);
                
                if (mercenary && monster->isAlive())
                {
                    int mercDmg = mercenary -> Attack();
                    monster->TakeDamage((int)mercDmg);
                    combatMessage += "\n=> [" + mercenary->name +  "] attacked! (Dmg: " + to_string(mercDmg) + ")";
                }
                
                if (monster->isAlive()) {
                    player.TakeDamage(monster->Attack());
                    cout << "   " << BRED << ">> The " << monster->GetName() << " retaliates!" << RESET
                        << RED << "  (-" << monster->Attack() << ")\n" << RESET;
                    Sleep(900);
                }
                else {
                    cout << "   " << BGREEN << ">> " << monster->GetName() << " is slain by your powerful blow!\n" << RESET;
                    Sleep(1300);
                }
            }
        }

        if (!monster->isAlive()) {
            player.GainExp(monster->GetExpReward());
            player.Loot(1);
        }
    }
    return player.isAlive();
}