assembler: main.o fpass.o structfunc.o checktxt.o spass.o action.o error.o createfiles.o utils.o prepro.o
	gcc -g -ansi -Wall -pedantic main.o fpass.o structfunc.o checktxt.o spass.o action.o error.o createfiles.o utils.o prepro.o -lm -o assembler

main.o: main.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic main.c -o main.o

prepro.o: prepro.c function.h global.h error.h utils.c createfiles.c
	gcc -c -ansi -Wall -pedantic prepro.c -o prepro.o

fpass.o: fpass.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic fpass.c -o fpass.o

structfunc.o: structfunc.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic structfunc.c -o structfunc.o

checktxt.o: checktxt.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic checktxt.c -o checktxt.o

spass.o: spass.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic spass.c -o spass.o

action.o: action.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic action.c -o action.o

error.o: error.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic error.c -o error.o

createfiles.o: createfiles.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic createfiles.c -o createfiles.o

utils.o: utils.c function.h global.h error.h
	gcc -c -ansi -Wall -pedantic utils.c -o utils.o

