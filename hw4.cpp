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
#include <cstring>
#include "message.h"

using namespace std;

int hw4::main(int argc, char* argv[]) {
	// Piping:  https://stackoverflow.com/questions/17508626/piping-for-input-output
	// open logger pipe - modified by Harrison 4/10/20

	if (pipe(loggerPipe)) {
		cout << "Failed to pipe" << endl;
	}

	arguments = CMDProcessor().Process(argc, argv);

	// added by Harrison 4/10/20
	cout << "DEBUGGING: checking list of arguments -->" << endl;
	for (auto const& pair:arguments)
		cout << "{" << pair.first << ":" << pair.second << "}" << endl;

	// Load log file - modified by Harrison 4/10/20
	try {
		logFileName = arguments.at('l');
	}
	catch (const out_of_range& oor) {
		logFileName = "log.txt";
	}

	int childLog = fork();
	if (childLog == -1) {
		cout << "An error has occurred" << endl;
		return 0;
	}
	else if (childLog == 0) {
		logStatus = logger();
		exit(0);
	}

	// Load rabbit file - modified by Harrison 4/10/20
	try {
		rabbitFileName = arguments.at('r');
		string message = "Loaded rabbit file: " + rabbitFileName;
		write(loggerPipe[1], message.c_str(), message.length() + 1);
	}
	catch (const out_of_range& oor) {
		string error = "Missing required file: rabbit";
		write(loggerPipe[1], error.c_str(), error.length() + 1);
		close(loggerPipe[1]);
		int status;
		wait(&status);
		return -1;
	}

	// Load knight file - modified by Harrison 4/10/20
	try {
		knightFileName = arguments.at('k');
		string message = "Loaded knight file: " + knightFileName;
		write(loggerPipe[1], message.c_str(), sizeof(message.c_str()));
	}
	catch (const out_of_range& oor) {
		char error[] = "Missing knight file, using default";
		write(loggerPipe[1], error, sizeof(error));
	}

	// modified by Harrison 4/10/20
	if (!knightFileName.empty()) {
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
		hw4().playGame();
	}

	// wait on logger to die

	// last open write end to the log -- closing it will cause read to return 0 (Harrison, 4/11/20)
	close(loggerPipe[1]);

	// wait for the logging process to complete and exit (Harrison, 4/11/20)
	int status;
	wait (&status);

	return 0;
} // end main

int hw4::logger() {
	// child process for log
	close(loggerPipe[1]);
	log = Log(logFileName);
	if(!log.open()) {
		cout << "Log failed to open - terminating application" << endl;
		kill(0, SIGTERM);
	}

	char message[LOG_MESSAGE_LENGTH];
	while (read(loggerPipe[0], message, LOG_MESSAGE_LENGTH)) {
		printf("Logger received: %s\n", message);
		log.writeLogRecord(string(message));
	}
	log.close();
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
	string message;
	
	message = "Knights: ";

	for (Knight k : knights)
	{
		//log.writeLogRecord(k.getName());
		message += \n + k.GetName();
		write(loggerPipe[1], message.c_str(), sizeof(message.c_str()));
	}

	// Display opening message
	message = "Let the game begin! ";
	write(loggerPipe[1], message.c_str(), sizeof(message.c_str()));

	/*
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
			//write(pipeToChild[1], (char*)&m, sizeof(message));
		}
		else if (attackChance <= (rabbit.getBite() + rabbit.getQuick())) {
			// rabbit chooses Quick Attack
			target = 0;
			for (Knight k : knights) {
				damage = Game().calcDamage(rabbit.getWeak());
				m.from = 0;
				m.type = 0;
				m.damage = damage;
				log.writeLogRecord(knights[target].getName() + " takes " + to_string(damage) + "damage from QuickAttack");

				// send message to knight
				//write(pipeToChild[1], (char*)&m, sizeof(message));
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
	*/
	message = "The game is over";
	write(loggerPipe[1], message.c_str(), sizeof(message.c_str()));



	cout << "Game has been played" << endl;

	return 0;