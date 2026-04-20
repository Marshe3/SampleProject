#include <iostream>
#include <string>
#include <cstdlib> // rand(), srand() 랜덤(주사위)를 섞는 함수
#include <ctime> // time() 현재 시간을 가져오는 함수


using namespace std;

int main() {
	
	cout << "Hello, World!\n";

	cout << "Hello, World!2" << endl;

	string userName;
	string charactorClass;
	char hardcoreInput;
	int classChoiceInput;

	//cout << "[ User Name ]\n";
	//cout << "input your name : ";

	//cin >> userName;

	//cout << "::::::::::Welcome to the D&D World ::::::::::\n";
	//cout << "User Name : [" << userName << "]!\n";
	
		// 스탯 시스템
	int strength = 50;
	int dexterity = 50;
	int vitality = 50;
	int energy = 50;
	

	//1. 다양한 자료형의 변수 선언 및 초기값 할당
	int level = 1;
	int hp = 100;
	int mp = 100;
	float attackSpeed = dexterity / 10.0f;
	float attackDamage = strength * 0.2f;
	double movingSpeed = dexterity / 30.0f;
	



	

	//  저항 시스템
	int fireResist = 0;
	int lightningResist = 0;
	int coldResist = 0;
	int poisonResist = 0;



	// 하드코어 모드 여부 변수
	bool isHardcore = true;

	cout << "[ Character Creation ]\n";
	cout << "Input your name : ";
	cin >> userName;
	
	cout << "Select your Class : \n";
	cout << "1. Amazon\n2. Assasion\n3. Basrbarian\n4. Druid\n";
	cout << "5. Necromancer\n6. Paladin\n7. Sorceress\n8. Warlock\n";
	cout << "Input your Class : ";
	cin >> classChoiceInput;

	switch (classChoiceInput)
	{
		case 1 : charactorClass = "Amazon"; break;
		case 2 : charactorClass = "Assasion"; break;
		case 3 : charactorClass = "Basrbarian"; break;
		case 4 : charactorClass = "Druid"; break;
		case 5 : charactorClass = "Necromancer"; break;
		case 6 : charactorClass = "Paladin"; break;
		case 7 : charactorClass = "Sorceress"; break;
		case 8 : charactorClass = "Warlock"; break;
	default:
		charactorClass = "Unknown";
		cout << "[System] Invalid class choice. Defaulting to 'Unknown'.\n";
		break;
	}


	cout << "\n:::::::::: Welcome to the Sanctuary ::::::::::\n";
	cout << "User Name : [" << userName << "]\n";
	cout << "Enable Hardcore Mode? (1) Yes / (2) No : ";
	cin >> hardcoreInput;

	// 하드코어 모드 여부 설정(if, else if,else 조건문 사용)
	if (hardcoreInput == '1') {
		isHardcore = true;
		cout << "[System]Hardcore Mode Enabled! Be careful, death is permanent!\n";
	}
	else if (hardcoreInput == '2') {
		isHardcore = false;
		cout << "[System]Standard Mode Enabled! You can respawn after death.\n";
	}
	else {
		cout << "[System]Invalid input. Defaulting to Standard Mode.\n";
		isHardcore = false;
	}



	// 2. 변수에 저장된 데이터 출력
	cout << "-----------Character Status-----------\n";
	cout << "Class : " << charactorClass << "\n";
	cout << "Level : " << level << "\n";
	cout << "HP : " << hp << "\n";
	cout << "MP : " << mp << "\n";
	cout << "Attack Speed : " << attackSpeed << "\n";
	cout << "Attack Damage : " << attackDamage << "\n";
	cout << "Moving Speed : " << movingSpeed << "\n";
	cout << "Strength : " << strength << "\n";
	cout << "Dexterity" << dexterity << "\n";
	cout << "Vitality : " << vitality << "\n";
	cout << "Energy : " << energy << "\n";
	cout << "Hardcore Mode : " << isHardcore << " (1: true, 0: false)\n";
	cout << "--------------------------------------\n";

	// 3. sizeof 연산자를 이용한 메모리 크기 확인
	cout << "[Memory Check] int type size: " << sizeof(hp) << "bytes\n";
	cout << "[Memory Check] bool type size: " << sizeof(isHardcore) << "bytes\n";

	// 4. 저항
	cout << "Fire Resistance : " << fireResist << "%\n";
	cout << "Lightning Resistance : " << lightningResist << "%\n";
	cout << "Cold Resistance : " << coldResist << "%\n";
	cout << "Poison Resistance : " << poisonResist << "%\n";
	
	// 기본 전투 시스템 -while문 사용(거짓일 때 까지 무한 루프)

	int goblinHp = 30; //고블린 체력
	int action;
	cout << "\n[SYstem] You encountered a Goblin!\n";

	//둘다 체력이 0보다 큰(살아잇는) 동안 무한 반복
	while (goblinHp > 0 && hp > 0) {
		cout << "\n[ Goblin HP: " << goblinHp << " I My HP: " << hp << " ]\n";
		cout << "1. Attack: ";
		cin >> action;

		if (action == 1) {
			// 공격
			goblinHp -= attackDamage;
			cout << "You attacked the Goblin (-" << attackDamage << ")\n";
			if (goblinHp > 0) {
				// 고블린 반격

				hp -= 30;
				cout << "=> The Goblin attacked you! (-30)\n";
			}
			else {
				cout << "=> Invalid action! Youstumbled and the Goblin seized the character!\n";
				hp -= 30;
				cout << "=> The Goblin attacked you! (-30)\n";
			}
		}
	}

		cout << "\n";
		if (hp <= 0) {
			cout << "[System]You died...\n";
			
		}
		else {
			cout << "[System] You defeated the Goblin!\n";
			
			// 난수 생성기 초기화 (매번 다른 아이템이 나오게 함)
			srand((unsigned int)time(NULL));

			cout << "----------Looting Items----------\n";

			// for문을 사용하여 3번 반복
			for (int i = 1; i <= 3; i++) {
				int lootRoll = rand() % 4; //0,1,2,3 중 하나의 난수 생성
				string itemName;

				// 뽑힌 숫자에 따라 아이템 이름 결정
				if (lootRoll == 0) {
					itemName = "GOld";
				}
				else if (lootRoll == 1){
					itemName = "Healing Potion";
				}
				else if (lootRoll == 2) {
					itemName = "Weapon";
				}
				else itemName = "Armor";
				//획득 결과 출력
				cout << i << ". Get [" << itemName << "]\n";
		}
			cout << "-------------------------------\n";
	}

	return 0;

}