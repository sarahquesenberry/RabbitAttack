#ifndef CMDPROCESSOR
#define CMDPROCESSOR


#include <map>
#include <string>
using namespace std;
// Create a map of key:value pairs of command args
class CMDProcessor {
public:
	map<char,string> Process(int argc, char* argv[]) {
		int numArgs = (argc - 1) / 2;
		map<char, string> argMap;

		for (int i = 1; i <= numArgs*2; i += 2) {
			char temp = argv[i][1]; // skip the dash and get char
			argMap.insert(pair<char, string>(temp, argv[i + 1]));
		}

		return argMap;
	}
};

#endif