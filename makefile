# Sarah Quesenberry 
# CSCI 4727-001
# 3/11/2020


hw6: hw6.o Game.o main.o Log.o Knight.o Rabbit.o CMDProcessor.o FileProcessor.o
	g++ hw6.o Game.o main.o Log.o Knight.o Rabbit.o CMDProcessor.o FileProcessor.o -o hw6
Game.o: Game.cpp Game.h
	g++ -c Game.cpp
main.o: main.cpp
	g++ -c main.cpp
hw6.o: hw6.cpp hw6.h
	g++ -c hw6.cpp
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
