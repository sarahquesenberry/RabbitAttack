#include <string>
#include "Log.h"
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

static const int SUCCESS = 1;
static const int FAILURE = 0;

string logfilename;
fstream logfile;


// Constructors
// Default
Log::Log() {
	setLogfilename("Log.txt");
	open();
	return;
}

// Overload: Character pointer
Log::Log(char* name) {
	std::string temp = "";

	while (*name != '\0') {
		temp += name;
		name++;
	}

	setLogfilename(temp);
	open();
	return;
}

// Overload: String
Log::Log(std::string name) {
	setLogfilename(name);
	open();
	return;
}


// Setter: Logfilename
void Log::setLogfilename(string name) {
	logfilename = name;
	return;
}


// Getter: Logfilename
string Log::getLogfilename() {
	return logfilename;
}


// Open log with timestamp
int Log::open() {

	logfile.open(logfilename, ios_base::app);
	logfile << "Begin" << endl;
	logfile << getTimeStamp() << endl;

	return SUCCESS;
}

// Close log with timestamp
int Log::close() {
	logfile << "End" << endl;
	logfile << getTimeStamp() << endl;

	logfile.close();

	return SUCCESS;
}


// Write string to log
int Log::writeLogRecord(string message) {

	logfile << message << endl;
	logfile << getTimeStamp() << endl;

	return SUCCESS;
}

// Get timestamp value
string Log::getTimeStamp() {
	// working with ctime
	// (http://www.cplusplus.com/reference/ctime/ctime/)
	time_t rawtime;
	time(&rawtime);
	return ctime(&rawtime);
}

