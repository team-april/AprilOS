main : prompt.o main.o command.o sls.o cdr.o mkr.o
	gcc -o main prompt.o main.o command.o sls.o cdr.o mkr.o

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

main.o : main.c
	gcc -c -o main.o main.c



clean :
	rm *.o main
