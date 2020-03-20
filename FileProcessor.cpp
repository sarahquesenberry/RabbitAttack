#ifndef FILEPROCESSOR
#define FILEPROCESSOR

#include <string>
#include <fstream>
#include <vector>
using namespace std;

class FileProcessor {
public:
	vector<string> Process(string fileName) {
		ifstream infile(fileName);
		vector<string> fileStream = {};
		string line;

		while (getline(infile, line)) {
			fileStream.push_back(line);
		}

		return fileStream;
	}
};

#endif