all: main
	
main:puzzle-static.c
	gcc -Wall -g -o main puzzle-static.c
test:
	valgrind ./main < test0 
	memusage ./main < test0
	valgrind ./main	< test1
	memusage ./main < test1
	valgrind ./main < test2
	memusage ./main < test2