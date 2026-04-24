#include <iostream>
#include <string>
#include <cstdlib>   // rand(), srand() 랜덤(주사위)를 섞는 함수
#include <ctime>     // time() 현재 시간을 가져오는 함수
#include <limits>    // [UI] numeric_limits - 입력 버퍼 처리용
#include "Player.h"
#include "Monster.h"

// [UI] windows.h가 max/min을 매크로로 정의해서 std::numeric_limits::max()와 충돌함
//      -> NOMINMAX를 먼저 정의해서 해당 매크로가 로드되지 않도록 차단
#define NOMINMAX
#include <windows.h> // [UI] ANSI 컬러 + Sleep() 활성화용

using namespace std;

// ==================================================================
// [UI] ANSI 이스케이프 컬러 매크로 - 콘솔에 색/스타일을 입히는 코드
// ==================================================================
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

// [UI] Windows 콘솔에서 ANSI 컬러 활성화
void enableConsoleStyles() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// [UI] 화면을 깨끗하게 지우는 함수
void clearScreen() {
    cout << "\033[2J\033[H\033[3J";
}

// [UI] "엔터를 눌러 계속" 프롬프트
void waitForEnter() {
    cout << "\n" << GRAY << "  [ Press ENTER to continue... ]" << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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

// ==================================================================
// [UI] 아스키 아트 - 고블린 스프라이트 출력 (HIGH QUALITY 업그레이드)
// ==================================================================
void printGoblinSprite(int currentHp, int maxHp) {
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

// Call By Address: 주소값 전달 -> 원본 변경 가능
void LevelUp(int* level) {
    (*level)++; // 포인터를 역참조하여 원본 변수의 값을 증가시킴
}

// Call By Reference: 참조자(Alias) 전달 -> 원본 변경 가능 (C++에서만 지원)
void LevelUpRef(int& level) {
    level++;
}

// Call By Reference: 예시) 참조자 전달 -> 실제 크리티컬 데미지 적용
void ApplyCriticalDamage(int& goblinHp, float attackDamage) {
	int criticalDamage = attackDamage * 2; // 크리티컬 데미지 계산
	goblinHp -= criticalDamage; // 원본 goblinHp 변수에 크리티컬 데미지 적용
}

//const 참조자 : 읽기 전용 참조자, 원본 변경 불가
void PrintLevel(const int& level) {
    cout << "현재 레벨 : " << level << "\n";
    // level++; // 컴파일 에러: const 참조자는 원본 변경 불가
}


// Monster 클래스



// player 클래스




int main() {
    enableConsoleStyles();

    // #####################################################
    // # [PAGE 1] 타이틀 + 캐릭터 이름 입력
    // #####################################################
    cout << "\n";
    cout << BRED << "  ====================================================\n" << RESET;
    cout << "\n";

    // [UI] DIABLO 아스키 로고
    cout << BYELLOW << R"(
    ____       _        _      ____    _        ___  
   |  _ \     | |      / \    | __ )  | |      / _ \ 
   | | | |    | |     / _ \   |  _ \  | |     | | | |
   | |_| |    | |    / ___ \  | |_) | | |___  | |_| |
   |____/     |_|   /_/   \_\ |____/  |_____|  \___/ 
)" << RESET;

    cout << "\n";
    cout << BYELLOW << "                  --- R E B O R N ---\n" << RESET;
    cout << "\n";
    cout << GRAY << "          ~ Welcome to the World of Sanctuary ~\n" << RESET;
    cout << "\n";
    cout << BRED << "  ====================================================\n" << RESET;
    cout << "\n";

    string userName;
    string charactorClass;
    char hardcoreInput;
     int classChoiceInput;
    bool isHardcore = true;


    

    system("pause");

 

    cout << BCYAN << "  +----- CHARACTER CREATION -----+\n" << RESET;
    cout << BCYAN << "  | " << BWHITE << " Enter your hero's name... " << BCYAN << "  |\n" << RESET;
    cout << BCYAN << "  +------------------------------+\n" << RESET;
    cout << BYELLOW << "  > Name: " << RESET;
    cin >> userName;
    
    waitForEnter();

    clearScreen();  // [TRANSITION] 페이지 전환 -> 클래스 선택

    // #####################################################
    // # [PAGE 2] 클래스 선택
    // #####################################################
    cout << "\n";
    cout << BMAGENTA << "  =========== CHOOSE YOUR CLASS ===========\n" << RESET;
    cout << "\n";
    cout << "   " << BYELLOW << "[1] " << BGREEN << "Amazon      " << GRAY << "- Plains huntress, master of the bow\n" << RESET;
    cout << "   " << BYELLOW << "[2] " << BMAGENTA << "Assassin    " << GRAY << "- Shadowborn martial artist\n" << RESET;
    cout << "   " << BYELLOW << "[3] " << BRED << "Barbarian   " << GRAY << "- Mountain-forged warrior\n" << RESET;
    cout << "   " << BYELLOW << "[4] " << BGREEN << "Druid       " << GRAY << "- Shapeshifter of the wilds\n" << RESET;
    cout << "   " << BYELLOW << "[5] " << MAGENTA << "Necromancer " << GRAY << "- Master of the dead\n" << RESET;
    cout << "   " << BYELLOW << "[6] " << BYELLOW << "Paladin     " << GRAY << "- Holy warrior of light\n" << RESET;
    cout << "   " << BYELLOW << "[7] " << BCYAN << "Sorceress   " << GRAY << "- Wielder of the elements\n" << RESET;
    cout << "   " << BYELLOW << "[8] " << BBLUE << "Warlock     " << GRAY << "- Arcane dark arts master\n" << RESET;
    cout << "\n";
    cout << BMAGENTA << "  =========================================\n" << RESET;
    cout << BYELLOW << "  > Choose your class (1-8): " << RESET;
    cin >> classChoiceInput;

    switch (classChoiceInput)
    {
    case 1: charactorClass = "Amazon";      break;
    case 2: charactorClass = "Assassin";    break;
    case 3: charactorClass = "Barbarian";   break;
    case 4: charactorClass = "Druid";       break;
    case 5: charactorClass = "Necromancer"; break;
    case 6: charactorClass = "Paladin";     break;
    case 7: charactorClass = "Sorceress";   break;
        
    case 8: charactorClass = "Warlock";     break;
    default:
        charactorClass = "Unknown";
        cout << "\n" << BRED << "  [System] Invalid class choice. Defaulting to 'Unknown'.\n" << RESET;
        Sleep(1500);
        break;
    }

    clearScreen();  // [TRANSITION] 페이지 전환 -> 생크추어리 + 하드코어

    // #####################################################
    // # [PAGE 3] 생크추어리 환영 + 하드코어 모드 선택
    // #####################################################
    cout << "\n";
    cout << BRED << "  ======= Welcome to the Sanctuary =======\n" << RESET;
    cout << BWHITE << "  User Name : " << BYELLOW << "[" << userName << "]\n" << RESET;
    cout << BWHITE << "  Class     : " << BMAGENTA << charactorClass << RESET << "\n";
    cout << "\n";

    cout << BRED << "  !! DIFFICULTY MODE !!\n" << RESET;
    cout << "   " << BYELLOW << "(1) " << BRED << "HARDCORE " << GRAY << "- Death is permanent\n" << RESET;
    cout << "   " << BYELLOW << "(2) " << BGREEN << "STANDARD " << GRAY << "- Respawn after death\n" << RESET;
    cout << BYELLOW << "  > Choice: " << RESET;
    cin >> hardcoreInput;

    cout << "\n";
    if (hardcoreInput == '1') {
        isHardcore = true;
        cout << BRED << "  [System] " << BOLD << "HARDCORE MODE ENABLED!" << RESET
            << BRED << " Be careful - death is permanent!\n" << RESET;
    }
    else if (hardcoreInput == '2') {
        isHardcore = false;
        cout << BGREEN << "  [System] Standard Mode Enabled. You can respawn after death.\n" << RESET;
    }
    else {
        cout << YELLOW << "  [System] Invalid input. Defaulting to Standard Mode.\n" << RESET;
        isHardcore = false;
    }
    Sleep(1500);

    clearScreen();  // [TRANSITION] 페이지 전환 -> 캐릭터 스탯 시트
    
    // Player 객체 생성 - 입력받은 값들로 초기화, 스탯은 내부에서 자동 계산됨
    Player player(userName, charactorClass, isHardcore);
    
    
    
    // #####################################################
    // # [PAGE 4] 캐릭터 스탯 시트
    // #####################################################
    cout << "\n";
    cout << BYELLOW << "  =============== CHARACTER STATUS ===============\n" << RESET;
    cout << "\n";
    cout << "   " << BWHITE << "Name   : " << RESET << BCYAN << player.GetName() << RESET << "\n";
    cout << "   " << BWHITE << "Class  : " << RESET << BMAGENTA << player.GetCharacterClass() << RESET << "\n";
    cout << "   " << BWHITE << "Level  : " << RESET << BYELLOW << player.GetLevel() << RESET << "\n";
    cout << "\n";
    cout << "   " << BRED << "HP  " << RESET << makeBar(player.GetHp(), player.GetMaxHp(), 20, BRED)
        << "  " << BRED << player.GetHp() << "/100\n" << RESET;
    cout << "   " << BBLUE << "MP  " << RESET << makeBar(player.GetMp(), player.GetMaxMp(), 20, BBLUE)
        << "  " << BBLUE << player.GetMp() << "/100\n" << RESET;
    cout << "\n";
    cout << GRAY << "   -- Combat --\n" << RESET;
    cout << "   " << BWHITE << "Attack Speed  : " << RESET << player.GetAttackSpeed() << "\n";
    cout << "   " << BWHITE << "Attack Damage : " << RESET << player.GetAttackDamage() << "\n";
    cout << "   " << BWHITE << "Moving Speed  : " << RESET << player.GetMovingSpeed() << "\n";
    cout << "\n";
    cout << GRAY << "   -- Attributes --\n" << RESET;
    cout << "   " << BRED << "STR " << RESET << player.GetStrength() << RESET << "\n   ";
    cout << BGREEN << "DEX " << RESET << player.GetDexterity() << "\n";
    cout << "   " << BYELLOW << "VIT " << RESET << player.GetVitality() << "   ";
    cout << BCYAN << "ENG " << RESET << player.GetEnergy() << "\n";
    cout << "\n";
    cout << "   " << BWHITE << "Hardcore Mode : " << RESET
        << (isHardcore ? BRED "ON " : BGREEN "OFF") << RESET
        << GRAY << "  (1=true, 0=false)\n" << RESET;
    cout << BYELLOW << "  ================================================\n" << RESET;

    cout << "\n";
    cout << GRAY << "  [Memory Check] int  type size : " << sizeof(player.GetHp()) << " bytes\n" << RESET;
    cout << GRAY << "  [Memory Check] bool type size : " << sizeof(isHardcore) << " bytes\n" << RESET;
    cout << "\n";
    
    cout << BMAGENTA << "  =============== RESISTANCES ===============\n" << RESET;
    cout << "   " << BRED << "  Fire      " << RESET << player.GetfireResist() << "%\n";
    cout << "   " << BYELLOW << "  Lightning " << RESET << player.GetLightningResist() << "%\n";
    cout << "   " << BCYAN << "  Cold      " << RESET << player.GetColdResist() << "%\n";
    cout << "   " << BGREEN << "  Poison    " << RESET << player.GetPoisonResist() << "%\n";
    cout << BMAGENTA << "  ===========================================\n" << RESET;

    waitForEnter();
    clearScreen();  // [TRANSITION] 페이지 전환 -> 전투

    // #####################################################
    // # [PAGE 5] 전투 시스템
    // #####################################################
    // 생성자 호출
    Monster goblin(30, 10);
    
   
    int action;

    cout << "\n";
    cout << BRED << "  >> ====== ENEMY ENCOUNTERED ====== <<\n" << RESET;
    printGoblinSprite(goblin.GetHp(), goblin.GetMaxHp());
    cout << "\n";
    cout << BGREEN << "      A wild " << BOLD << "Goblin" << RESET
        << BGREEN << " emerges from the shadows!\n" << RESET;
    cout << "\n";
    Sleep(2000);

    while (goblin.isAlive() && player.isAlive()) {
        clearScreen();

        cout << "\n";
        cout << BRED << "  >> ========== BATTLE ========== <<\n" << RESET;

        printGoblinSprite(goblin.GetHp(), goblin.GetMaxHp());

        cout << GRAY << "  ------------------------------------------\n" << RESET;
        cout << "   " << BGREEN << "Goblin " << RESET << makeBar(goblin.GetHp(), goblin.GetMaxHp(), 15, BGREEN)
            << "  " << BGREEN << goblin.GetHp() << "/" << goblin.GetMaxHp() << "\n" << RESET;
        cout << "   " << BRED << "You    " << RESET << makeBar(player.GetHp(), player.GetMaxHp(), 15, BRED)
            << "  " << BRED << player.GetHp() << "/100\n" << RESET;
        cout << GRAY << "  ------------------------------------------\n" << RESET;
        cout << "\n";
        cout << "   " << BYELLOW << "[1] Attack      [2] Critical Attack\n" << RESET;
        cout << BYELLOW << "  > Action: " << RESET;
        cin >> action;

        if (action == 1) {
            goblin.TakeDamage((int)player.GetAttackDamage());
            cout << "\n";
            cout << "   " << BYELLOW << ">> You strike the Goblin!" << RESET
                << RED << "  (-" << player.GetAttackDamage() << ")\n" << RESET;
            Sleep(500);
            if (goblin.isAlive() && player.isAlive()) {
                player.TakeDamage(goblin.Attack());
                cout << "   " << BRED << ">> The Goblin retaliates!" << RESET
                    << RED << "  (-30)\n" << RESET;
                Sleep(900);
            }
            else {
                cout << "   " << BGREEN << ">> The Goblin is slain!\n" << RESET;
                player.TakeDamage(30);
                cout << "   " << BRED << ">> The Goblin attacked you!" << RESET
                    << RED << "  (-30)\n" << RESET;
                Sleep(1300);
            }
        }
        else if (action == 2) {
            PreviewCritical(player.CriticalAttack());
            goblin.TakeDamage((int)player.CriticalAttack());

            cout << "\n";
            cout << "   " << BMAGENTA << ">> CRITICAL STRIKE! " << BYELLOW << "You deal massive damage!" << RESET
                << RED << " (-" << player.CriticalAttack() << ")\n" << RESET;
            Sleep(500);

            if (goblin.isAlive()) {
                player.TakeDamage(30);
                cout << "   " << BRED << ">> The Goblin retaliates!" << RESET
                    << RED << "  (-30)\n" << RESET;
                Sleep(900);
            }
            else {
                cout << "   " << BGREEN << ">> The Goblin is slain by your powerful blow!\n" << RESET;
                player.TakeDamage(goblin.Attack());
                cout << "   " << BRED << ">> The Goblin's final struggle hits you!" << RESET
                    << RED << "  (-30)\n" << RESET;
                Sleep(1300);
            }
        } 

    }

    clearScreen();  // [TRANSITION] 페이지 전환 -> 전투 결과

    // #####################################################
    // # [PAGE 6] 전투 결과 + 루팅
    // #####################################################
    cout << "\n";
    if (player.GetHp() <= 0) {
        cout << BRED << R"(
                _____
               /     \
              | () () |
              |   >   |
               \ --- /
                |||||
               /|||||\
)" << RESET;
        Sleep(600);
        cout << "\n";
        cout << BRED << "  ==========================================\n" << RESET;
        Sleep(400);
        cout << BRED << "           +  Y O U   D I E D  +\n" << RESET;
        Sleep(900);
        cout << GRAY << "      The darkness claims another soul...\n" << RESET;
        Sleep(500);
        cout << BRED << "  ==========================================\n" << RESET;
    }
    else {
        // [UI] 승리 연출 - 대검(Greatsword) 아스키 아트 (이전과 완벽히 동일)
        cout << BCYAN << R"(
                      /\
                     /  \
                    |    |
                    |    |
                    |    |
                    |    |
                    |    |
                    |    |
                    |    |
                ___/______\___)" << "\n"
            << BYELLOW << R"(               [____    ____]
                 \_ \  / _/
                   \_\/_/
                     ||
                     ||
                     ||
                    _||_
                    \__/
)" << RESET;
        Sleep(600);
        cout << "\n";
        cout << BYELLOW << "  ==========================================\n" << RESET;
        Sleep(400);
        cout << BYELLOW << "          * V I C T O R Y !  *\n" << RESET;
        Sleep(900);
        cout << BGREEN << "       The Goblin falls at your feet.\n" << RESET;
        Sleep(500);
        cout << BYELLOW << "  ==========================================\n" << RESET;
        Sleep(700);

        srand((unsigned int)time(NULL));

        cout << "\n";
        cout << BMAGENTA << "  +---- LOOT DROPPED ----+\n" << RESET;
        Sleep(400);

        int* invPtr = player.GetInventory(); //invPtr -> gameInventory 시작주소 [0]
        
        // 포인터로 인벤토리에 랜덤 숫자 저장
        for (int i = 1; i <= 3; i++) {
            *invPtr = rand() % 4 + 1; // 역참조로 현재 칸에 아이템 코드를 저장하고자 함
            invPtr++; // 다음 칸으로 포인터 이동
        }
        cout << BYELLOW << "  ==========================================\n";
           //포인터 순회로 인벤토리 출력(5칸)
		invPtr = player.GetInventory(); // invPtr을 다시 시작주소로 초기화
        int slot = 0;

        while (invPtr < player.GetInventory() + 5) { // invPtr이 배열 끝 주소보다 작은 동안 반복
            
            string itemName;
            if (*invPtr == 1) itemName = "Gold";
            else if(*invPtr == 2) itemName = "Healing Potion";
            else if (*invPtr == 3) itemName = "Weapon";
            else if (*invPtr == 4) itemName = "Armor";
			else itemName = "Empty Slot";


            cout << " > Slot " << slot <<  " [" << itemName << "]\n";
            invPtr++; // 다음 칸으로 포인터 이동
            slot++;   // 슬롯 번호 증가
        }

        // 레벨업
        player.LevelUp();
        player.PrintLevel();
        cout << BYELLOW << "  ==========================================\n";
    }

    cout << "\n";

    waitForEnter();

    

    return 0;
}