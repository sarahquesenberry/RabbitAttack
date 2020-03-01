#include "fork2.h"
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;
// Credits
// Creating a process
//  https://www.tutorialspoint.com/how-to-create-a-process-in-linux

// Using fork, execv, and wait
//  http://www.cs.ecu.edu/karl/4630/spr01/example1.html

int main(int argc, char* argv[]) {
	int child = fork();
	pid_t child_pid;
	pid_t tpid;
	int childStatus = 0;

	if (child == -1) {
		cout << "An error has occured" << endl;
		return 0;
	}
	else if (child == 0) {
		// create child process
		childStatus = fork2().child_function(argv);
	}
	else {
		// parent code
		childStatus = fork2().parent_function(argv, child_pid, tpid, childStatus);
		return childStatus;
	}

	return 0;
}

int fork2::child_function(char* argv[]){
	cout << "Child PID: " << getpid() << endl;
	cout << "Parent PID: " << getppid() << endl;

	execv("hw2", argv);

	exit(0);

	return 0;
}

int fork2::parent_function(char* argv[], pid_t child_pid, pid_t tpid, int childStatus){
	cout << "Parent code reached" << endl;

	while((tpid = wait(&childStatus)) > 0);

	system("cat logfile.txt");
	
	return childStatus;
}