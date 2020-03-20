#include "hw4.h"
#include <unistd.h>
#include <iostream>
#include "Log.h"
#include "Rabbit.h"
#include "Knight.h"
#include "Game.h"
#include <string>
#include "CMDProcessor.cpp"
#include "FileProcessor.cpp"
#include <map>
#include <iterator>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include "message.h"


using namespace std;



int hw4::main(int argc, char* argv[]) {

		// Piping:  https://stackoverflow.com/questions/17508626/piping-for-input-output
		// open pipes
		

		if (pipe(pipeToChild) != 0 || pipe(pipeFromChild) != 0) {
			cout << "Failed to pipe" << endl;
		}


		arguments = CMDProcessor().Process(argc, argv);


		// Load log file
		try {
			logFileName = arguments.at('l');
		}
		catch (int e) {
			logFileName = "log.txt";
		}

		int childLog = fork();
		if (childLog == -1) {
			cout << "An error has occured" << endl;
			return 0;
		}
		else if (childLog == 0) {
			logStatus = hw4().makeLog();
			exit(0);
		}
		else {


			while (wait(&logStatus) > 0);


			// Load rabbit file

			try {
				rabbitFileName = arguments.at('r');
				log.writeLogRecord("Loaded rabbit file: " + rabbitFileName);
			}
			catch (int e) {
				log.writeLogRecord("Missing required file: rabbit");
				return 0;
			}

			// Load knight file
			try {
				knightFileName = arguments.at('k');
				log.writeLogRecord("Loaded knight file: " + knightFileName);
			}
			catch (int e) {
				log.writeLogRecord("Missing knight file, using default");
			}


			// Read file contents



				// Create knights

			if (knightFileName != "") {
				kFileContents = FileProcessor().Process(knightFileName);

				ss << kFileContents[0];
				getline(ss, trash, ':');
				getline(ss, trash, ':');
				count = stoi(trash);
				ss.clear();

				// fork for each knight
				for (int i = 2; i / 6 < count; i += 6) {
					int childKnight = fork();
					if (childKnight == -1) {
						cout << "An error has occured" << endl;
						return 0;
					}
					else if (childKnight == 0) {
						knightStatus = hw4().makeKnight(i);
						exit(0);
					}
				}

			}
			else {
				int childKnight = fork();
				if (childKnight == -1) {
					cout << "An error has occured" << endl;
					return 0;
				}
				else if (childKnight == 0) {
					knightStatus = hw4().makeKnight();
					exit(0);
				}
			}


			// Create rabbit
			rFileContents = FileProcessor().Process(rabbitFileName);
			values.clear();
			for (string x : rFileContents) {
				ss << x;
				getline(ss, trash, ':');
				getline(ss, trash, ':');
				values.push_back(trash);
				ss.clear();
			}

			int childRabbit = fork();
			if (childRabbit == -1) {
				cout << "An error has occured" << endl;
				return 0;
			}
			else if (childRabbit == 0) {
				rabbitStatus = hw4().makeRabbit();
				exit(0);
			}
			else {

				// wait for knights and rabbit creation
				while (wait(&knightStatus) > 0);
				while (wait(&rabbitStatus) > 0);


				// Parent --> child
				// main --> Log --> KnightA --> KnightB --> ... --> Rabbit 



				// begin simulation
				return hw4().playGame();
			}


		return 0;
	}
} // end main








int hw4::makeLog() {
	// child process for log
	log = Log(logFileName);
	log.writeLogRecord("Loaded log file: " + logFileName);
	exit(0);
}






int hw4::makeKnight() {
	// child process for default knight
	knight = Knight();
	knights.push_back(knight);
	exit(0);
}






int hw4::makeKnight(int i) {
	// child process for knight
	ss << kFileContents[i];
	getline(ss, trash, ':');
	getline(ss, trash, ':');
	values.push_back(trash);
	ss.clear();

	ss << kFileContents[(int)i + 1];
	getline(ss, trash, ':');
	getline(ss, trash, ':');
	values.push_back(trash);
	ss.clear();

	ss << kFileContents[(int)i + 2];
	getline(ss, trash, ':');
	getline(ss, trash, ':');
	values.push_back(trash);
	ss.clear();

	ss << kFileContents[(int)i + 3];
	getline(ss, trash, ':');
	getline(ss, trash, ':');
	values.push_back(trash);
	ss.clear();

	ss << kFileContents[(int)i + 4];
	getline(ss, trash, ':');
	getline(ss, trash, ':');
	values.push_back(trash);
	ss.clear();

	knight = Knight(values);
	knights.push_back(knight);
	values.clear();



	exit(0);
}






int hw4::makeRabbit() {
	// child process for rabbit
	rabbit = Rabbit(values);
	exit(0);
}






int hw4::playGame() {
	// cycle through knights and rabbit (each checks for damage then attacks)
	bool victor = false;
	int attackChance = 0;
	int target;
	int damage;
	
	
	message m;
	// from:
	//	rabbit = 0
	//	first Knight = 1
	//	second Knight = 2 ...
	// type: 
	//	bite = 0;
	//	throat = 1;
	//	quick = 2;
	//	first Knight = 3 ...


	// Display players
	log.writeLogRecord("Knights:");

	for (Knight k : knights)
	{
		log.writeLogRecord(k.getName());
	}

	// Display opening message
	log.writeLogRecord("Let the game begin!");

	// while the game is still playing
	while (!victor) {
		target = rand() % knights.size() + 0;

		attackChance = rand() % 100 + 1;
		if (attackChance <= rabbit.getBite()) {
			//rabbit chooses bite
			damage = Game().calcDamage(rabbit.getWeak());
			m.from = 0;
			m.type = 0;
			m.damage = damage;
			log.writeLogRecord(knights[target].getName() + " takes " + to_string(damage) + "damage from Bite");

			// send message to knight
			write(pipeToChild[1], (char*)&m, sizeof(message));
		}
		else if (attachChange <= (rabbit.getBite() + rabbit.getQuick())) {
			// rabbit chooses Quick Attack
			target = 0;
			for (Knight k : knights) {
				damage = Game().calcDamage(rabbit.getWeak());
				m.from = 0;
				m.type = 0;
				m.damage = damage;
				log.writeLogRecord(knights[target].getName() + " takes " + to_string(damage) + "damage from QuickAttack");

				// send message to knight
				write(pipeToChild[1], (char*)&m, sizeof(message));
				target++;
			}
		}
		else {
			// rabbit chooses Throat
			damage = Game().calcDamage(rabbit.getStrong());
			m.from = 0;
			m.type = 0;
			m.damage = damage;
			log.writeLogRecord(knights[target].getName() + " takes " + to_string(damage) + "damage from Throat");

			// send message to knight
			write(pipeToChild[1], (char*)&m, sizeof(message));
		}

		for (Knight k : knights) {
			attackChance = rand() % 100 + 1;

			if (rabbit.getEvade() < attackChance) {
				damage = Game().calcDamage(k.getDamage());
				log.writeLogRecord("Rabbit took " + to_string(damage) + " from " + k.getName());
			}
			else {
				log.writeLogRecord(k.getName() + " attempts to attack the rabbit but misses!");
			}
		}


		if (!rabbit.getStatus()) {
			// if the rabbit was slain
			log.writeLogRecord("The rabbit has been slain. The knights are victorious!");

		}
		else if (knights.size() > 0) {
			// if the knights were slain
			log.writeLogRecord("The knights have been slain. The rabbit is victorious!");
		}


	}
	cout << "Game has been played" << endl;

	return 0;
}