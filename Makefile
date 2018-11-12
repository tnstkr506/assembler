# Write this Makefile
myas: check.o trans.o main.o
	gcc -o myas trans.o check.o main.o -lm
check.o: check.c
	gcc -c check.c
trans.o: trans.c
	gcc -c trans.c
main.o: main.c
	gcc -c main.c
clean:
	rm -rf check.o trans.o main.o myassembler

