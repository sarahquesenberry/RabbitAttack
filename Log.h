#pragma once
#ifndef LOG
#define LOG

#include <string>
#include <fstream>
using namespace std;

class Log {

private:
	static const int SUCCESS = 1;
	static const int FAILURE = 0;

	string logfilename;		// Log file name
	fstream logfile;		// Log file variable

	string getTimeStamp();	// Get timestamp value

public:
	Log();				// Default constructor
	Log(char* name);	// Overload character array
	Log(string name);	// Overload string 

	void setLogfilename(string name);	// Setter: logfilename
	string getLogfilename();			// Getter: logfilename

	int open();		// Open log with timestamp
	int close();	// Close log with timestamp

	int writeLogRecord(string message);	// Write string to log

};// end class log

#endif