# Sarah Quesenberry 
# CSCI 4727-001
# 3/11/2020


hw4: hw4.o game.o main.o Log.o Knight.o Rabbit.o CMDProcessor.o FileProcessor.o
	g++ hw4.o game.o main.o Log.o Knight.o Rabbit.o CMDProcessor.o FileProcessor.o -o hw4
game.o: Game.cpp Game.h
	g++ -c Game.cpp
main.o: main.cpp
	g++ -c main.cpp
hw4.o: hw4.cpp hw4.h
	g++ -c hw4.cpp
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
clean:
	rm *.o
