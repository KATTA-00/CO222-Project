all: mainT mainM 
	
mainM:puzzle-dynamic.c
	gcc -Wall -g -o mainM puzzle-dynamic.c
mainT:puzzle-dynamicT.c
	gcc -Wall -g -o mainT puzzle-dynamicT.c
install:
	sudo apt-get install valgrind
memtest:
	valgrind ./mainM < test0 
	memusage ./mainM < test0
	valgrind ./mainM	< test1
	memusage ./mainM < test1
	valgrind ./mainM < test2
	memusage ./mainM < test2
timetest:
	./mainT < test0 
	./mainT	< test1
	./mainT < test2