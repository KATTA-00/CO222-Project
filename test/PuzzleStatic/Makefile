all: mainT mainM
	
mainM:puzzle-static.c
	gcc -Wall -g -o mainM puzzle-static.c
mainT:puzzle-staticT.c
	gcc -Wall -g -o mainT puzzle-staticT.c
memtest:
	valgrind ./mainM < test0 
	memusage ./mainM < test0
	valgrind ./mainM < test1
	memusage ./mainM < test1
	valgrind ./mainM < test2
	memusage ./mainM < test2
timetest:
	./mainT < test0 
	./mainT	< test1
	./mainT < test2