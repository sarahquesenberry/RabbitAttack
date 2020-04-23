#include "Rabbit.h"
#include <string>
#include <vector>
#include "message.h"

using namespace std;

// Constructor
Rabbit::Rabbit() {
	setHP(0);
	setAttackRate(0);
	setBite(0);
	setQuick(0);
	setThroat(0);
	setWeak(0);
	setStrong(0);
	setEvade(0);
	setStatus(true);
}

// Overload: file given
Rabbit::Rabbit(vector<string> valueStream) {
	setHP(stoi(valueStream[0]));
	setAttackRate(stoi(valueStream[1]));
	setBite(stoi(valueStream[2]));
	setQuick(stoi(valueStream[3]));
	setThroat(stoi(valueStream[4]));
	setWeak(stoi(valueStream[5]));
	setStrong(stoi(valueStream[6]));
	setEvade(stoi(valueStream[7]));
	setStatus(true);
}



// Combat
int Rabbit::takeDamage(int damageDealt) {
	this->hp -= damageDealt;

	// if health drops to 0, rabbit  is dead
	if (this->hp <= 0) {
		setStatus(false);
		return damageDealt;
	}

	return damageDealt;
}
