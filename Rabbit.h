#pragma once
#ifndef RABBIT_H
#define RABBIT_H

#include <vector>
#include <string>
using namespace std;

class Rabbit {

private:
	int hp;				// [25,100]
	int attackRate;		// [3,10]
	int bite;			// [60,75]
	int quick;			// [10,20]
	int throat;			// [5,20]
	int weak;			// [1,9]
	int strong;			// [30,40]
	int evade;			// [5,95]
	bool status;		// Active or inactive(dead)

public:
	Rabbit();
	Rabbit(vector<string> valueStream);

	// Getters
	int getHP() { return hp; }
	int getAttackRate() { return attackRate; }
	int getBite() { return bite; }
	int getQuick() { return quick; }
	int getThroat() { return throat; }
	int getWeak() { return weak; }
	int getStrong() { return strong; }
	int getEvade() { return evade; }
	bool getStatus() { return status; }

	// Setters
	void setHP(int hp) { this->hp = hp; }
	void setAttackRate(int attackRate) { this->attackRate = attackRate; }
	void setBite(int bite) { this->bite = bite; }
	void setQuick(int quick) { this->quick = quick; }
	void setThroat(int throat) { this->throat = throat; }
	void setWeak(int weak) { this->weak = weak; }
	void setStrong(int strong) { this->strong = strong; }
	void setEvade(int evade) { this->evade = evade; }
	void setStatus(bool status) { this->status = status; }

	int takeDamage(int damageDealt);

};
#endif