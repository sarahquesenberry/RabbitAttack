#pragma once
#ifndef HW4
#define HW4

#include "Log.h"
#include "Knight.h"
#include "Rabbit.h"
#include "CMDProcessor.cpp"
#include "FileProcessor.cpp"
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <wait.h>
#include <unistd.h>

using namespace std;

class hw4{
private:
    vector<Knight> knights;
    Rabbit rabbit;
    Log log;

public:
    int LogProc();
    int KnightProc();
    int RabbitProc();

    int PlayGame();

};



#endif