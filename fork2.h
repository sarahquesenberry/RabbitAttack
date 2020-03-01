#pragma once
#ifndef FORK2
#define FORK2

#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <iostream>

class fork2{
public:
    int child_function(char* argv[]);
    int parent_function(char* argv[], pid_t child_pid, pid_t , int childStatus);
};

#endif