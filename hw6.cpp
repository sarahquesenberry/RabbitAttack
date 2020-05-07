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





//shared data structures
queue<string> messageQueue;
map<char, string> arguments;

// thread stuff from Harrison's einstein
pthread_t r, k;
pthread_barrier_t barrier;

pthread_mutex_t lock;


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
    
    while(read(loggerPipe[0], message, sizeof(message)) > 0){
        cout << "Logger received: " << message << endl;
        log.writeLogRecord(string(message));
    }

    cout << "Close log" << endl;
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
void* rabbitThread(void*){
    pthread_mutex_lock(&lock);
    cout << "Rabbit Thread ran" << endl;
    pthread_mutex_unlock(&lock);
    //pthread_barrier_wait(&barrier);

    string messageR;

    for(int i = 0; i < 6; i++){
        messageR = "Rabbit attack " + to_string(i);
        pthread_mutex_lock(&lock);
        messageQueue.push(messageR);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    pthread_exit(NULL);
}



// Thread KNIGHT
void* knightThread(void*){
    pthread_mutex_lock(&lock);
    cout << "Knight Thread ran" << endl;
    pthread_mutex_unlock(&lock);
    //pthread_barrier_wait(&barrier);

    string messageK;

    for(int i = 0; i < 6; i++){
        messageK = "Knight attack " + to_string(i);
        pthread_mutex_lock(&lock);
        messageQueue.push(messageK);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }


    pthread_exit(NULL);
}

void check_error(int errno, int status_code){
		if(errno){
			perror(strerror(errno));
			exit(status_code);
		}
	}






int main(int argc, char* argv[]) {

    
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
        logStatus = logger();
        exit(0);
    }


    //DEBUG
    m = makeMessage(4,2,19);
    
    close(loggerPipe[0]); //close read end

    write(loggerPipe[1], m.sendMessage(), m.contents.length() + 1);

    

    int errno;

    //pthread_barrier_init(&barrier, 0, 2);

    // create rabbitThread()
    cout << "Rabbit Thread creation" << endl;
    errno = pthread_create(&r, NULL, rabbitThread, NULL);
    //hw6().check_error(errno, 42);

    // create knightThread()
    cout << "Knight Thread creation" << endl;
    errno = pthread_create(&k, NULL, knightThread, NULL);
    //hw6().check_error(errno, 42);

    cout << "Join r" << endl;
    errno = pthread_join(r, NULL);
    //hw6().check_error(errno, 42);
    cout << "Join k" << endl;
    errno = pthread_join(k, NULL);
    //hw6().check_error(errno, 42);

    //fflush(stdout);

    cout << "Sleepy time..." << endl;
    sleep(3);

    cout << "PRINT" << endl;
    while(!messageQueue.empty()){
        cout << messageQueue.front() << endl;
        messageQueue.pop();
    }


    close(loggerPipe[1]);
    
    cout << "Wait for log process" << endl;
    wait(NULL);

    
    cout << "End of file" << endl;
    return 0;
}