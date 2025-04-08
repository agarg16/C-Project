main: main.o pwd.o cd.o
	gcc -o main main.o pwd.o cd.o
main.o: main.c pwd.h cd.h directory.h
	gcc -c main.c
pwd.o: pwd.c directory.h
	gcc -c pwd.c
cd.o: cd.c directory.h
	gcc -c cd.c
