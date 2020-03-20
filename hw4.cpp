#include "hw4.h"

using namespace std;

int main(int argc, char* argv[]){
    cout << "I am main" << endl;
    
    
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


    // Create knights
    if (knightFileName != "") {
        kFileContents = FileProcessor().Process(knightFileName);

        ss << kFileContents[0];
        getline(ss, trash, ':');
        getline(ss, trash, ':');
        count = stoi(trash);
        ss.clear();

        for (int i = 2; i / 6 < count; i += 6) {
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


    #pragma openmp parallel
    {
        #pragma openmp atomic{
        foreach(Knight k in knights) {
            int childKnight = fork();
            int knightStatus = 0;
            if (childKnight == -1) {
                cout << "An error has occured" << endl;
                return 0;
            }
            if (childKnight == 0) {
                // create Knight proccess
                knightStatus = hw4().KnightProc();
            }
        }
        }

        int childRabbit = fork();
        int rabbitStatus = 0;
        if (childRabbit == -1) {
            cout << "An error has occured" << endl;
            return 0;
        }
        if (childRabbit == 0) {
            // create Rabbit proccess
            rabbitStatus = hw4().RabbitProc();
        }
    }
   
    while(wait(&logStatus) > 0);
    while(wait(&knightStatus) > 0);
    while(wait(&rabbitStatus) > 0);

    hw4().PlayGame();
    

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