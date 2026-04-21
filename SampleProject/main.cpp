#include <iostream>
#include <string>
#include <cstdlib>   // rand(), srand() 랜덤(주사위)를 섞는 함수
#include <ctime>     // time() 현재 시간을 가져오는 함수
#include <limits>    // [UI] numeric_limits - 입력 버퍼 처리용

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

    // 스탯 시스템
    int strength = 50;
    int dexterity = 50;
    int vitality = 50;
    int energy = 50;

    // 1. 다양한 자료형의 변수 선언 및 초기값 할당
    int level = 1;
    int hp = 100;
    int mp = 100;
    float attackSpeed = dexterity / 10.0f;
    float attackDamage = strength * 0.2f;
    double movingSpeed = dexterity / 30.0f;

    // 저항 시스템
    int fireResist = 0;
    int lightningResist = 0;
    int coldResist = 0;
    int poisonResist = 0;

    // 하드코어 모드 여부 변수
    bool isHardcore = true;

	// "&" 연산자와 변수 주소값 출력 예시
	cout << "hp변수의 값 : " << hp << "\n";
	cout << "hp변수의 주소값 : " << &hp << "\n"; // 변수의 주소값 출력 & 연산자
	system("pause"); // 변수 값과 주소값을 확인하기 위한 일시정지

	// "*" 역참조 연산자와 포인터 변수 예시
	int* ptr = &hp; // hp 변수의 주소값을 ptr 포인터에 저장
    cout << "ptr == &hp: " << ptr << "\n";
	cout << "*ptr 값 : " << *ptr << "\n"; // ptr이 가리키는 주소의 값 출력 (hp의 값)
	*ptr = 200; // ptr을 통해 hp의 값을 200으로 변경
	cout << "hp변수의 새로운 값 : " << hp << "\n"; // hp의 값이 변경된 것을 확인

   /// int* ptr2;
	//cout << "ptr2 (초기값) : " << ptr2 << "\n"; // 초기화되지 않은 포인터 변수의 값 (쓰레기값)

    system("pause"); // 변수 값과 주소값을 확인하기 위한 일시정지

    cout << "sizeot(int) : " << sizeof(int) << "bytes \n";
    cout << "sizeot(int) : " << sizeof(int*) << "bytes \n";
    cout << "sizeot(int) : " << sizeof(float*) << "bytes \n";
    cout << "sizeot(int) : " << sizeof(char*) << "bytes \n";

    system("pause"); // 변수 값과 주소값을 확인하기 위한 일시정지
    
	//포인터 연산 (+1 = 자료형 크기만큼 주소 이동)
	cout << "ptr (현재값) : " << ptr << "\n";
    cout << "ptr (현재값) : " << ptr + 1 << "\n";
    cout << "ptr (현재값) : " << ptr + 2 << "\n";

    system("pause");

    int scores[5] = { 85, 92, 78, 95,88 };
    cout << "&scores[0] :" << &scores[0] << "\n";
    cout << "&scores[1] :" << &scores[1] << "\n";
    cout << "&scores[2] :" << &scores[2] << "\n";
    cout << "&scores[3] :" << &scores[3] << "\n";
    cout << "&scores[4] :" << &scores[4] << "\n";

    system("pause");


    system("pause");

	// 배열 이름이 시작 주소로  형변환(Pointer Decay)되는 예시
	cout << "scores: " << scores << "\n";
	cout << "&scores[0]" << &scores[0] << "\n";
    cout << "scoret[2] :" << scores[2] << "\n";
	cout << *"scores+2] :" << *scores + 2 << "\n"; // scores[2]의 값 출력
    system("pause");

 // 형변환의  예외상황 1. sizeof()사용
    cout << "sizeof(scores) : " << sizeof(scores) << "\n";
	cout << "sizeof(scores[0]) : " << sizeof(scores[0]) << "\n";
	cout << "scores 원소개수 : " << sizeof(scores) / sizeof(scores[0]) << "\n"; // 배열의 원소 개수 계산

	//형변환의  예외상황 2. (주소)연산자 사용
	cout << "sizeof(&scores) : " << sizeof(&scores) << "\n"; // 시작주소
    cout << "scores + 1 : " << scores +1 << "\n"; // +4 원소 단위로 int 만큼
	cout << "&scores : " << &scores << "\n"; // 시작주소
	cout << "&scores + 1 : " << &scores + 1 << "\n"; // // +20 배열 전체 단위로 이동

    system("pause");
    // for 반복문을 통한 배열 순환
    int* sPtr = scores;
    for (int i = 0; i < 5; i++) {
        cout << "주소 :" << sPtr << " 값 : " << *sPtr << "\n";
        sPtr++; // +1 포인터 연산으로 다음 원소 주소로 이동
    }

    // Wild Pointer 위험
	//int* wildPtr; // 초기화되지 않은 포인터 변수 (와일드 포인터)
	//*wildPtr = 100; // 와일드 포인터를 역참조하여 값을 할당 (정의되지 않은 동작, 프로그램 충돌 가능)

    // 포인트 변수 선언 시 안전한 초기화 예시문
	int* wildPtr = nullptr; // 와일드 포인터를 nullptr로 초기화하여 안전하게 처리
	if (wildPtr != nullptr) { // nullptr 체크를 통해 안전하게 역참조 여부 판단
        *wildPtr = 100; // 안전하게 역참조하여 값을 할당
    }
	cout << "wildPtr : " << wildPtr << "\n"; // nullptr 출력

    system("pause");


    system("pause"); 
    cout << BCYAN << "  +----- CHARACTER CREATION -----+\n" << RESET;
    cout << BCYAN << "  | " << BWHITE << " Enter your hero's name... " << BCYAN << "  |\n" << RESET;
    cout << BCYAN << "  +------------------------------+\n" << RESET;
    cout << BYELLOW << "  > Name: " << RESET;
    cin >> userName;
    
    system("pause");

    
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

    // #####################################################
    // # [PAGE 4] 캐릭터 스탯 시트
    // #####################################################
    cout << "\n";
    cout << BYELLOW << "  =============== CHARACTER STATUS ===============\n" << RESET;
    cout << "\n";
    cout << "   " << BWHITE << "Name   : " << RESET << BCYAN << userName << RESET << "\n";
    cout << "   " << BWHITE << "Class  : " << RESET << BMAGENTA << charactorClass << RESET << "\n";
    cout << "   " << BWHITE << "Level  : " << RESET << BYELLOW << level << RESET << "\n";
    cout << "\n";
    cout << "   " << BRED << "HP  " << RESET << makeBar(hp, 100, 20, BRED)
        << "  " << BRED << hp << "/100\n" << RESET;
    cout << "   " << BBLUE << "MP  " << RESET << makeBar(mp, 100, 20, BBLUE)
        << "  " << BBLUE << mp << "/100\n" << RESET;
    cout << "\n";
    cout << GRAY << "   -- Combat --\n" << RESET;
    cout << "   " << BWHITE << "Attack Speed  : " << RESET << attackSpeed << "\n";
    cout << "   " << BWHITE << "Attack Damage : " << RESET << attackDamage << "\n";
    cout << "   " << BWHITE << "Moving Speed  : " << RESET << movingSpeed << "\n";
    cout << "\n";
    cout << GRAY << "   -- Attributes --\n" << RESET;
    cout << "   " << BRED << "STR " << RESET << strength << "   ";
    cout << BGREEN << "DEX " << RESET << dexterity << "\n";
    cout << "   " << BYELLOW << "VIT " << RESET << vitality << "   ";
    cout << BCYAN << "ENG " << RESET << energy << "\n";
    cout << "\n";
    cout << "   " << BWHITE << "Hardcore Mode : " << RESET
        << (isHardcore ? BRED "ON " : BGREEN "OFF") << RESET
        << GRAY << "  (1=true, 0=false)\n" << RESET;
    cout << BYELLOW << "  ================================================\n" << RESET;

    cout << "\n";
    cout << GRAY << "  [Memory Check] int  type size : " << sizeof(hp) << " bytes\n" << RESET;
    cout << GRAY << "  [Memory Check] bool type size : " << sizeof(isHardcore) << " bytes\n" << RESET;
    cout << "\n";

    cout << BMAGENTA << "  =============== RESISTANCES ===============\n" << RESET;
    cout << "   " << BRED << "  Fire      " << RESET << fireResist << "%\n";
    cout << "   " << BYELLOW << "  Lightning " << RESET << lightningResist << "%\n";
    cout << "   " << BCYAN << "  Cold      " << RESET << coldResist << "%\n";
    cout << "   " << BGREEN << "  Poison    " << RESET << poisonResist << "%\n";
    cout << BMAGENTA << "  ===========================================\n" << RESET;

    waitForEnter();
    clearScreen();  // [TRANSITION] 페이지 전환 -> 전투

    // #####################################################
    // # [PAGE 5] 전투 시스템
    // #####################################################
    int goblinHp = 30;  // 고블린 체력
    int goblinMaxHp = 30;
    int action;

    cout << "\n";
    cout << BRED << "  >> ====== ENEMY ENCOUNTERED ====== <<\n" << RESET;
    printGoblinSprite(goblinHp, goblinMaxHp);
    cout << "\n";
    cout << BGREEN << "      A wild " << BOLD << "Goblin" << RESET
        << BGREEN << " emerges from the shadows!\n" << RESET;
    cout << "\n";
    Sleep(2000);

    while (goblinHp > 0 && hp > 0) {
        clearScreen();

        cout << "\n";
        cout << BRED << "  >> ========== BATTLE ========== <<\n" << RESET;

        printGoblinSprite(goblinHp, goblinMaxHp);

        cout << GRAY << "  ------------------------------------------\n" << RESET;
        cout << "   " << BGREEN << "Goblin " << RESET << makeBar(goblinHp, goblinMaxHp, 15, BGREEN)
            << "  " << BGREEN << goblinHp << "/" << goblinMaxHp << "\n" << RESET;
        cout << "   " << BRED << "You    " << RESET << makeBar(hp, 100, 15, BRED)
            << "  " << BRED << hp << "/100\n" << RESET;
        cout << GRAY << "  ------------------------------------------\n" << RESET;
        cout << "\n";
        cout << "   " << BYELLOW << "[1] Attack\n" << RESET;
        cout << BYELLOW << "  > Action: " << RESET;
        cin >> action;

        if (action == 1) {
            goblinHp -= attackDamage;
            cout << "\n";
            cout << "   " << BYELLOW << ">> You strike the Goblin!" << RESET
                << RED << "  (-" << attackDamage << ")\n" << RESET;
            Sleep(500);
            if (goblinHp > 0) {
                hp -= 30;
                cout << "   " << BRED << ">> The Goblin retaliates!" << RESET
                    << RED << "  (-30)\n" << RESET;
                Sleep(900);
            }
            else {
                cout << "   " << BGREEN << ">> The Goblin is slain!\n" << RESET;
                hp -= 30;
                cout << "   " << BRED << ">> The Goblin attacked you!" << RESET
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
    if (hp <= 0) {
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

        for (int i = 1; i <= 3; i++) {
            int lootRoll = rand() % 4;
            string itemName;
            string itemColor;
            string itemIcon;

            if (lootRoll == 0) {
                itemName = "Gold";
                itemColor = BYELLOW;
                itemIcon = "$";
            }
            else if (lootRoll == 1) {
                itemName = "Healing Potion";
                itemColor = BRED;
                itemIcon = "+";
            }
            else if (lootRoll == 2) {
                itemName = "Weapon";
                itemColor = BCYAN;
                itemIcon = "/";
            }
            else {
                itemName = "Armor";
                itemColor = BWHITE;
                itemIcon = "[";
            }
            cout << "   " << BMAGENTA << "[" << i << "]" << RESET
                << " " << itemColor << itemIcon << "  " << itemName << RESET << "\n";
            Sleep(500);
        }
        cout << BMAGENTA << "  +----------------------+\n" << RESET;
    }
    cout << "\n";

    waitForEnter();

    return 0;
}