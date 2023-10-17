#pragma once
#ifndef STAFF_H
#include "role.h"
#include "magician.h"
#include <string>
#include <iostream>
using namespace std;

class Staff {
public:
	Staff(string staffName) :name(staffName), damage(10) {

	}
	void equipable(Role* role) {
		// TODO : refer to spec
		if (isMagician(role)) {
			cout << role->getID() << " can equip staff_flame." << endl;
		}
		else {
			cout << "error bad cast" << endl;
		}
	}

private:
	string name;
	int damage;
	bool isMagician(Role* role) {
		// TODO : refer to spec
		Magician* mag = dynamic_cast<Magician*>(role);
		if (mag == NULL) {
		 	  return false;
		}
		else {
		 	  return true;
		}
	}
};
#endif
#pragma once
