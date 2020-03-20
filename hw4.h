#ifndef MAIN
#define MAIN

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

class main {
public:
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

	int logStatus = 0;
	int knightStatus = 0;
	int rabbitStatus = 0;

public:
	//int main(int argc, char* argv[]);

	int makeLog();
	int makeKnight();
	int makeKnight(int i);
	int makeRabbit();
	int playGame();



};

#endif