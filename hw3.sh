#!/bin/bash

# run me with "bash hw3.sh"

if [ -e "makefile" ]; then
	make
	./fork2 $@
else
	echo "No makefile detected"
fi
