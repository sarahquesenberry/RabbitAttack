#pragma once
#ifndef KNIGHT
#define KNIGHT

#include <vector>
#include <string>
using namespace std;

class Knight {

private:
	string name;	// [2,50]
	int hp;			// [10,40]
	int bravery;	// [0, < hp]
	int attackRate;	// [10,50]
	int damage;		// [1,8]
	bool status;	// Active or inactive (dead or fled)


public:
	Knight();
	Knight(vector<string> valueStream);

	// Getters
	string getName() { return name; }
	int getHP() { return hp; }
	int getBravery() { return bravery; }
	int getAttackRate() { return attackRate; }
	int getDamage() { return damage; }
	bool getStatus() { return status; }

	// Setters
	void setName(string name) { this->name = name; }
	void setHP(int hp) { this->hp = hp; }
	void setBravery(int bravery) { this->bravery = bravery; }
	void setAttackRate(int attackRate) { this->attackRate = attackRate; }
	void setDamage(int damage) { this->damage = damage; }
	void setStatus(bool status) { this->status = status; }

	
	int takeDamage(int damageDealt);
};
#endif