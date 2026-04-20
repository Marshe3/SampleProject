#include <iostream>
#include <string>
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
	

	return 0;

}