#include <string>
#include "Log.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <signal.h>

using namespace std;

static const int SUCCESS = 1;
static const int FAILURE = 0;

string logfilename;
fstream logfile;


// Constructors
// Default
Log::Log() {
	setLogfilename("log.txt");
}

// Overload: Character pointer
Log::Log(char* name) {
	std::string temp = "";

	while (*name != '\0') {
		temp += name;
		name++;
	}

	setLogfilename(temp);
}

// Overload: String
Log::Log(std::string name) {
	setLogfilename(name);
}


// Setter: Logfilename
void Log::setLogfilename(string name) {
	logfilename = name;
}


// Getter: Logfilename
string Log::getLogfilename() {
	return logfilename;
}


// Open log with timestamp
int Log::open() {

	logfile.open(logfilename, ios_base::app);

	if (logfile.bad())
		return FAILURE;

	logfile << getTimeStamp() << "Begin\n" << endl;

	return SUCCESS;
}

// Close log with timestamp
int Log::close() {

	logfile << getTimeStamp() << "End" << endl;
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

