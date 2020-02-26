#pragma once
#ifndef GAME_H
#define GAME_H
#include "Log.h"
#include "Rabbit.h"
#include "Knight.h"
#include <string>
#include <vector>
#include <stdlib.h>

class Game {
private:
	Log log;

public:
	void PlayGame(Rabbit rabbit, vector<Knight> knights, Log& log);
	int calcDamage(int playerDamage);
};
#endif