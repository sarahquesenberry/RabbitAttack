#include "hw6.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "Rabbit.h"
#include "Knight.h"
#include "Log.h"
#include "CMDProcessor.cpp"
#include "FileProcessor.cpp"
#include "Game.h"
#include "message.h"
#include <queue>
#include <map>
#include <iterator>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

//shared data structures
queue<message> messageQueue;



int hw6::main(int argc, char* argv[]) {

    // Using queues: http://www.cplusplus.com/reference/queue/queue/

    // open pipe
    if (pipe(loggerPipe) < 0) {
		cout << "Failed to pipe" << endl;
		exit(1);
	}


    // Create Log process
    int childLog = fork();
    if(childLog == -1){
        cout << "An error has occurred" << endl; 
        return 0;
    }
    else if(childLog == 0){
        logStatus = logger();
        exit(0);
    }


    // Create Game process
    int childGame = fork();
    if(childGame == -1){
        cout << "An error has occured" << endl;
        return 0;
    }
    else if(childGame == 0){
        gameStatus = game();
        exit(0);
    }

    


    // Wait for both to exit
    cout << "Wait for log process" << endl;
    wait(&logStatus);
    cout << "Wait for game process" << endl;
    wait(&gameStatus);

    return 0;
}

int hw6::logger(){

    logFileName = "logfile.txt";
    close(loggerPipe[1]); //close write end
    log = Log(logFileName);
    if(!log.open()){
        cout << "Log failed to open" << endl;
        kill(0, SIGTERM);
    }

    char message[4];
    while(read(loggerPipe[0], message, 4) > 0){
        cout << "Logger received: " << message << endl;
        log.writeLogRecord(string(message));
    }

    log.close();
    cout << "Log process successful" << endl;
    exit(0);
}

int hw6::game(){

    string num1 = "123";
    string num2 = "345";
    string num3 = "456";
    close(loggerPipe[0]); //close read end

    write(loggerPipe[1], num1.c_str(), 4);
    write(loggerPipe[1], num2.c_str(), 4);
    write(loggerPipe[1], num3.c_str(), 4);

    close(loggerPipe[1]);
    cout << "Game process successful" << endl;
    return 0;
}

hw6::message hw6::makeMessage(int from, int type, int damage){
    message m;

    m.from = from;
    m.type = type;
    m.damage = damage;

    return m;
}