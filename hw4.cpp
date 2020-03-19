#include "hw4.h"

using namespace std;

int main(int argc, char* argv[]){
    cout << "I am main" << endl;
    
    
    
    


    #pragma openmp parallel

    int childLog = fork();
    int logStatus = 0;
    if(childLog == -1){
        cout << "An error has occured" << endl;
        return 0;
    }
    if(childLog == 0){
        // create Log proccess
        logStatus = hw4().LogProc();
    }

    int childKnight = fork();
    int knightStatus = 0;
    if(childKnight == -1){
        cout << "An error has occured" << endl;
        return 0;
    }
    if(childKnight == 0){
        // create Knight proccess
        knightStatus = hw4().KnightProc();
    }

    int childRabbit = fork();
    int rabbitStatus = 0;
    if(childRabbit == -1){
        cout << "An error has occured" << endl;
        return 0;
    }
    if(childRabbit == 0){
        // create Rabbit proccess
        rabbitStatus = hw4().RabbitProc();
    }

    while(wait(&logStatus) > 0);
    while(wait(&knightStatus) > 0);
    while(wait(&rabbitStatus) > 0);

    hw4().PlayGame();
    
    // Process Log file

    // fork Log

    // Process Knight file

    // fork Knights (each knight gets a fork)

    // Process Rabbit file

    // fork Rabbit (each Rabbit gets a fork)
    cout << "I am done..." << endl;
    return 0;
}

int hw4::LogProc(){
    // Open log file
    cout << "I am Log" << endl;
    exit(0);
}

int hw4::KnightProc(){
    // Create a Knight 

    // Open pipe to rabbit and log
    cout << "I am Knight" << endl;
    exit(0);
}

int hw4::RabbitProc(){
    // Create a rabbit

    // Open pipe to knights and log
    cout << "I am Rabbit" << endl;
    exit(0);
}

int hw4::PlayGame(){
    // Play game until there is a victor

    cout << "Play the game!" << endl;
    exit(0);
}