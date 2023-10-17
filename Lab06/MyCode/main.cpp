#include "role.h"
#include "magician.h"
#include "warrior.h"
#include "archer.h"
#include "staff.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;



int main() {
	ifstream file("input2.txt");
	char num[3];
	file.getline(num, sizeof(num), '\n');
	int number = atoi(num);
	Role** role;
	role = new Role* [number];
	for (int i = 0; i < number; i++)
	{
		char id[10];
		char career[10];
		char level[5];
		char money[10];
		char hp[10];
		file.getline(id, sizeof(id), ','); file.get();
		file.getline(career, sizeof(career), ','); file.get();
		file.getline(level, sizeof(level), ','); file.get();
		file.getline(money, sizeof(money), ','); file.get();
		file.getline(hp, sizeof(hp));
		string id_str;
		int level_int, money_int, hp_int;
		int j = 0;
		id_str += id;
		/*
		while (id[j] != '\0')
		{
			id_str += id[j];
			j++;
		}
		*/
		level_int = atoi(level);
		money_int = atoi(money);
		hp_int = atoi(hp);
		switch (career[0])
		{
		case 'W':
			role[i] = new Warrior(id_str, level_int, money_int, hp_int);
			break;
		case 'A':
			role[i] = new Archer(id_str, level_int, money_int, hp_int);
			break;
		case 'M':
			role[i] = new Magician(id_str, level_int, money_int, hp_int);
			break;
		default:
			break;
		}
		role[i]->printAllInfo();
		role[i]->ShowRole();
		cout << endl;
	}
	// TODO : Read the file
	// 1. Read the input file to get the imformation

	// TODO : Create the Role according to the input file
	// 1. Create the role
	// 2. Print this role's Infomation
	// 3. Show Role ( refer to spec )
	// Example :
	// -------------------------------------------------------
	// Role* warrior = new Warrior( warrior's Name, warrior's Level, warrior's Money, warrior's HP);
	// warrior->printAllInfo();
	// warrior->ShowRole();
	// cout << endl;
	// 
	// Role* archer = new Archer(archer's Name, archer's Level, archer's Money, archer's HP);
	// archer->printAllInfo();
	// archer->ShowRole();
	// cout << endl;
	// 
	// Role* magician = new Magician(magician's Name, magician's Level, magician's Money, magician's HP);
	// magician->printAllInfo();
	// magician->ShowRole();
	// cout << endl;
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles


	Staff* staff = new Staff("flame");
	cout << "Checking whether the role can equip a staff.." << endl;
	for (int i = 0; i < number; i++)
	{
		staff->equipable(role[i]);
	}
	//
	// TODO : Check wheather all characters can get staff or not
	// Example :
	// -------------------------------------------------------
	// staff->equipable(warrior);
	// staff->equipable(archer);
	// staff->equipable(magician);
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles
	cout << endl;

	for (int i = 0; i < number; i++)
		delete role[i];

	system("PAUSE");
	return 0;
}
