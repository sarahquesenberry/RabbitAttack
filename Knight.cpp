#include "Knight.h"
#include <string>
#include <vector>
#include "message.h"

using namespace std;


// Constructors
// Default
Knight::Knight(){
	setName("Sir Knight");
	setHP(20);
	setBravery(5);
	setAttackRate(20);
	setDamage(5);
	setStatus(true);
}

// Overload: file given
Knight::Knight(vector<string> valueStream) {
	setName(valueStream[0]);
	setHP(stoi(valueStream[1]));
	setBravery(stoi(valueStream[2]));
	setAttackRate(stoi(valueStream[3]));
	setDamage(stoi(valueStream[4]));
	setStatus(true);
}



// Combat related
int Knight::takeDamage(int damageDealt){
	this->hp -= damageDealt;

	// if health drops below bravery, knight will flee
	if (this->hp <= this->bravery) {
		setStatus(false);
		return damageDealt;
	}

	// if health drops to 0, knight is dead
	if (this->hp <= 0) {
		setStatus(false);
		return damageDealt;
	}

	return damageDealt;
}