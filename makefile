#makefile

target: projet.o main.o
	g++ projet.o main.o -o proj

projet.o: projet.cpp
	g++ -c projet.cpp projet.h
main.o: main.cpp
	g++ -c main.cpp projet.h

clean : 
	rm -f *.o
