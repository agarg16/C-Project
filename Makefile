main: fork.o main.o cmds.o directory.o sigint.o catart.o tabcomp.o
	gcc -o main fork.o main.o cmds.o directory.o sigint.o catart.o tabcomp.o
fork.o: fork.c
	gcc -c fork.c
main.o: main.c
	gcc -c main.c
cmds.o: cmds.c
	gcc -c cmds.c
directory.o: directory.c
	gcc -c directory.c
sigint.o: sigint.c
	gcc -c sigint.c
catart.o: catart.c
	gcc -c catart.c
tabcomp.o: tabcomp.c
	gcc -c tabcomp.c