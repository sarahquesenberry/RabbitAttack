#pragma once
#ifndef HW6
#define HW6


#include <iostream>
#include "Log.h"
#include "Rabbit.h"
#include "Knight.h"
#include "Game.h"
#include "message.h"
#include <string>
#include "CMDProcessor.cpp"
#include "FileProcessor.cpp"
#include <map>
#include <iterator>
#include <vector>
#include <sstream>


class hw6{
private:
    
    
    
public:

    int main(int argc, char* argv[]);

    int logger();
    int game();
	int makeKnight();
	int makeKnight(int i);
	int makeRabbit();
	int playGame();
    message makeMessage(int from, int type, int damage);

	static void* rabbitThread();
	static void* knightThread();

	void check_error(int errno, int status_code);
	
};



#endif