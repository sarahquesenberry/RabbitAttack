#include "hw4.h"
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

using namespace std;



void hw4::main(int argc, char* argv[]) {
	

	// Piping:  https://stackoverflow.com/questions/17508626/piping-for-input-output
	// open pipes
	int pipeToChild[2];
	int pipeFromChild[2];
	int bytesRead;

	if (pipe(pipeToChild) != 0 || pipe(pipeFromChild) != 0) {
		cout << "Failed to pipe" << endl;
	}


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
	if (childLog == 0) {
		logStatus = main().makeLog();
	}


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
	

#pragma openmp parallel{
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
			if (childKnight == 0) {
				knightStatus = main().makeKnight(i);
			}
		}

	}
	else {
		int childKnight = fork();
		if (childKnight == -1) {
			cout << "An error has occured" << endl;
			return 0;
		}
		if (childKnight == 0) {
			knightStatus = main().makeKnight();
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
	if (childRabbit == 0) {
		rabbitStatus = main().makeRabbit();
	}


	}// end pragma openmp parallel

	
	// wait for knights and rabbit creation
	while (wait(&knightStatus) > 0);
	while (wait(&rabbitStatus) > 0);


	// Parent --> child
	// main --> Log --> KnightA --> KnightB --> ... --> Rabbit 



	// begin simulation
	return main().playGame();
	

	return 0;
} // end main


int hw4::makeLog() {
	// child process for log
	Log log = Log(logFileName);
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
	//bool victor = false;

	// while the game is still playing
	//while (!victor) {

	//}


	return 0;
}