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
        cout << "Fork to LOG" << endl;
        logStatus = hw6().logger();
        exit(0);
    }


    //DEBUG
    string num1 = "123";
    
    close(loggerPipe[0]); //close read end

    write(loggerPipe[1], num1.c_str(), sizeof(num1) + 1);

    close(loggerPipe[1]);
    cout << "Game process successful" << endl;


    /*
    // create rabbitThread()
    errno = pthread_create(&r, NULL, rabbitThread, NULL);
    check_error(errno, 42);

    // create knightThread()
    errno = pthread_create(&k, NULL, knightThread, NULL);
    check_error(errno, 42);

    errno = pthread_join(r, NULL);
    check_error(errno, 42);
    errno = pthread_join(k, NULL);
    check_error(errno, 42);

    fflush(stdout);
    return 0;
    */

    
    cout << "Wait for log process" << endl;
    wait(NULL);

    
    cout << "End of file" << endl;
    return 0;
}

int hw6::logger(){

    logFileName = "logFile.txt";
    close(loggerPipe[1]); //close write end
    log = Log(logFileName);
    if(!log.open()){
        cout << "Log failed to open" << endl;
        kill(0, SIGTERM);
    }

    cout << "Logfile opened" << endl;
    char message[LOG_MESSAGE_LENGTH];
    /*
    while(read(loggerPipe[0], message, LOG_MESSAGE_LENGTH) > 0){
        cout << "Logger received: " << message << endl;
        log.writeLogRecord(string(message));
    }
    */
    read(loggerPipe[0], message, sizeof(message));
    cout << "Logger received: " << string(message) << endl;

    log.close();
    cout << "Log process successful" << endl;
    exit(0);
}


hw6::message hw6::makeMessage(int from, int type, int damage){
    message m;

    m.from = from;
    m.type = type;
    m.damage = damage;

    return m;
}



// Thread RABBIT
//void *rabbitThread(){
//
//    pthread_barrier_wait(&barrier);
//    pthread_exit(0);
//}



// Thread KNIGHT
//void *knightThread(){
//    pthread_barrier_wait(&barrier);
//    pthread_exit(0);
//}