#include "fork2.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;
// Creating a process
//  https://www.tutorialspoint.com/how-to-create-a-process-in-linux
int fork2::main() {
	int child = fork();

	if (child == -1) {
		cout << "An error has occured" << endl;
		return 0;
	}
	else if (value == 0) {
		// create child process
		cout << "Child PID: " << getpid() << endl;
		cout << "Parent PID: " << getppid() << endl;
	}
	else {
		// parent code
	}
}