# Sarah Quesenberry 
# CSCI 4727-001
# 2/19/2020
# Based on code given in Barrett-Makefile Basics and einstein example

hw2: Log.o Knight.o Rabbit.o CMDProcessor.o FileProcessor.o Game.o main.o
	g++ Log.o Knight.o Rabbit.o CMDProcessor.o FileProcessor.o Game.o main.o -o hw2
Log.o: Log.cpp Log.h
	g++ -c Log.cpp 
Knight.o: Knight.cpp Knight.h 
	g++ -c Knight.cpp
Rabbit.o: Rabbit.cpp Rabbit.h
	g++ -c Rabbit.cpp
CMDProcessor.o: CMDProcessor.cpp
	g++ -c CMDProcessor.cpp 
FileProcessor.o: FileProcessor.cpp
	g++ -c FileProcessor.cpp
Game.o: Game.cpp Game.h
	g++ -c Game.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o
