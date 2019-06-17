main : prompt.o main.o command.o sls.o cdr.o mkr.o MAN.o chm.o pdr.o shw.o
	gcc -o main prompt.o main.o command.o sls.o cdr.o mkr.o MAN.o chm.o pdr.o shw.o

prompt.o : prompt.c
	gcc -c -o prompt.o prompt.c

command.o : command.c
	gcc -c -o command.o command.c

sls.o : sls.c
	gcc -c -o sls.o sls.c

cdr.o : cdr.c
	gcc -c -o cdr.o cdr.c

mkr.o : mkr.c
	gcc -c -o mkr.o mkr.c

MAN.o : MAN.c
	gcc -c -o MAN.o MAN.c

chm.o : chm.c
	gcc -c -o chm.o chm.c

pdr.o : pdr.c
	gcc -c -o pdr.o pdr.c

shw.o : shw.c
	gcc -c -o shw.o shw.c

main.o : main.c
	gcc -c -o main.o main.c



clean :
	rm *.o main
