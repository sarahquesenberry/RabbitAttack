#include "Game.h"
#include <string>
#include <vector>
#include <stdlib.h>


void Game::PlayGame(Rabbit rabbit, vector<Knight> knights, Log& log) {
	int turnCounter = 0;
	int attackChance = 0;
	int target;
	int damage;

	// Display players
	log.writeLogRecord("Knights:");

	for (Knight k : knights)
	{
		log.writeLogRecord(k.getName());
	}

	// Display opening message
	log.writeLogRecord("Let the game begin!");


	// while rabbit is alive and at least one knight is alive 
	while (rabbit.getStatus() && knights.size() > 0) {
		// rabbit attacks first upon tie
		if (turnCounter % rabbit.getAttackRate() == 0) {
			// select target
			target = rand() % knights.size() + 0;

			// choose attack
			attackChance = rand() % 100 + 1; // Random number between 1 - 100
			if (attackChance <= rabbit.getBite())
			{
				// rabbit chooses Bite
				damage = knights[target].takeDamage(calcDamage(rabbit.getWeak()));
				log.writeLogRecord("Rabbit -- Target: " + knights[target].getName() + "; Attack Type: Bite; Damage: " + to_string(damage));
				
				if (knights[target].getHP() <= 0) { // if knight is dead
					log.writeLogRecord(knights[target].getName() + " has been slain by Bite!");
					knights.erase(knights.begin() + target); // remove knight from target list
				}
				else if (!knights[target].getStatus()) { // if knight has fled
					log.writeLogRecord(knights[target].getName() + " runs away from Bite. Coward!");
					knights.erase(knights.begin() + target); // remove knight from target list
				}
			}
			else if (attackChance <= (rabbit.getBite() + rabbit.getQuick())) {
				// rabbit chooses Quick Attack
				target = 0;
				for (Knight k : knights) {
					damage = k.takeDamage(calcDamage(rabbit.getWeak()));
					log.writeLogRecord("Rabbit -- Target: " + k.getName() + "; Attack Type: Quick Attack; Damage: " + to_string(damage));

					if (k.getHP() <= 0) { // if knight has died
						log.writeLogRecord(k.getName() + " has been slain by Quick Attack!");
						knights.erase(knights.begin() + target); // remove knight from target list
					}
					else if (!k.getStatus()) { // if knight has fled
						log.writeLogRecord(k.getName() + " runs away from Quick Attack. Coward!");
						knights.erase(knights.begin() + target); // remove knight from target list
					}
					target++; // increment target index counter
				}
			}
			else {
				// rabbit chooses Throat
				damage = knights[target].takeDamage(calcDamage(rabbit.getStrong()));
				log.writeLogRecord("Rabbit -- Target: " + knights[target].getName() + "; Attack Type: Throat Attack; Damage: " + to_string(damage));

				if (knights[target].getHP() <= 0) { // if knight is dead
					log.writeLogRecord(knights[target].getName() + " has been slain by Throat Attack!");
					knights.erase(knights.begin() + target); // remove knight from target list
				}
				else if (!knights[target].getStatus()) { // if knight has fled
					log.writeLogRecord(knights[target].getName() + " runs away from Throat Attack. Coward!");
					knights.erase(knights.begin() + target); // remove knight from target list
				}
			}
		}

		for (Knight k : knights) {
			if (turnCounter % k.getAttackRate() == 0) {
				// Get chance to hit
				attackChance = rand() % 100 + 1; // Random number between 1 - 100
				
				// if knight successfully hits
				if (rabbit.getEvade() < attackChance) {
					damage = rabbit.takeDamage(calcDamage(k.getDamage()));
					log.writeLogRecord(k.getName() + " -- Target: Rabbit; Damage: " + to_string(damage));
				}
				else {
					log.writeLogRecord(k.getName() + " attempts to attack the rabbit but misses!");
				}
			}
		}

		turnCounter++; // next turn
	}

	if (!rabbit.getStatus()) { // if rabbit was slain
		log.writeLogRecord("The rabbit has been slain. The knights are victorious!");
	}
	else { // the knights were slain
		log.writeLogRecord("The knights have been slain. The rabbit is victorious!");
	}

	// Display closing statement
	log.writeLogRecord("The game is over, thank you for playing");

	// Close log file
	log.close();
	return;
}


// Damage is variable and can be (+/-)3 from posted player damage
int Game::calcDamage(int playerDamage) {
	int startRange = playerDamage - 3;
	int endRange = playerDamage + 3;
	int delta = endRange - startRange;

	return rand() % delta + startRange;
}
