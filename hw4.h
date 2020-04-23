#pragma once
#ifndef HW4
#define HW4

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

class hw4 {
private:
	map<char, string> arguments;
	string logFileName = "";
	string rabbitFileName = "";
	string knightFileName = "";

	vector<string> rFileContents;
	vector<string> kFileContents;

	string trash;
	stringstream ss;
	vector<string> values;
	int count;

	Log log;

	Rabbit rabbit;

	Knight knight;
	vector<Knight> knights;

	int logStatus = 0;
	int knightStatus = 0;
	int rabbitStatus = 0;

	// modified by Harrison 4/10/20
	int loggerPipe[2], rabbitPipe[2];
	int *knightPipes;
	int bytesRead;

	static const int LOG_MESSAGE_LENGTH = 64;

	struct message {
		int from;
		int type;
		int damage;
	};

public:
	int main(int argc, char* argv[]);

	int logger();
	int makeKnight();
	int makeKnight(int i);
	int makeRabbit();
	int playGame();



};

#endif