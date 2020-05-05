//#include "hw6.h"
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




	

class hw6{
//shared data structures
queue<message> messageQueue;
map<char, string> arguments;

// thread stuff from Harrison's einstein
pthread_t r, k;
pthread_barrier_t barrier;


string logFileName;
string rabbitFileName;
string knightFileName;

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
message m;

int logStatus;
int gameStatus;

int loggerPipe[2];
int rabbitPipe[2];
int *knightPipes;
int bytesRead;

static const int LOG_MESSAGE_LENGTH = 64;






int main(int argc, char* argv[]) {

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
    m = makeMessage(4,2,19);
    
    close(loggerPipe[0]); //close read end

    write(loggerPipe[1], m.sendMessage(), m.contents.length() + 1);

    

    int errno;

    //pthread_barrier_init(&barrier, 0, 2);

    // create rabbitThread()
    pthread_create(&r, NULL, hw6::rabbitThread, NULL);
    //hw6().check_error(errno, 42);

    // create knightThread()
    //errno = pthread_create(&k, NULL, hw6::knightThread, NULL);
    //hw6().check_error(errno, 42);

    errno = pthread_join(r, NULL);
    //hw6().check_error(errno, 42);
    //errno = pthread_join(k, NULL);
    //hw6().check_error(errno, 42);

    //fflush(stdout);


    close(loggerPipe[1]);
    
    cout << "Wait for log process" << endl;
    wait(NULL);

    
    cout << "End of file" << endl;
    return 0;
}



int logger(){

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


message makeMessage(int from, int type, int damage){
    message m;

    m.from = from;
    m.type = type;
    m.damage = damage;

    return m;
}



// Thread RABBIT
void* rabbitThread(){
    cout << "Rabbit Thread ran" << endl;
    //pthread_barrier_wait(&barrier);

    //fflush(stdout);
    //pthread_exit(NULL);
}



// Thread KNIGHT
//void *knightThread(){
//    cout << "Knight Thread ran" << endl;
    //pthread_barrier_wait(&barrier);

    //fflush(stdout);
//    pthread_exit(NULL);
//}

void check_error(int errno, int status_code){
		if(errno){
			perror(strerror(errno));
			exit(status_code);
		}
	}
};