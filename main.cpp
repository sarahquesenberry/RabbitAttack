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


int main(int argc, char* argv[]) {
	
	map<char, string> arguments = CMDProcessor().Process(argc, argv);
	string logFileName = "";
	string rabbitFileName = "";
	string knightFileName = "";

	vector<string> rFileContents;
	vector<string> kFileContents;

	string trash;
	stringstream ss;
	vector<string> values;
	int count;

	Rabbit rabbit;

	Knight knight;
	vector<Knight> knights;


	// Load log file
	try {
		logFileName = arguments.at('l');
	}
	catch (int e) {
		logFileName = "log.txt";
	}

	Log log = Log(logFileName);
	log.writeLogRecord("Loaded log file: " + logFileName);


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

		for (int i = 2; i/6 < count; i+=6) {
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
		}

	}
	else {
		knight = Knight();
		knights.push_back(knight);
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

	rabbit = Rabbit(values);



	// Begin game
	Game().PlayGame(rabbit, knights, log);
	

	return 0;
} // end main