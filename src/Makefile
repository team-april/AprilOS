main : prompt.o main.o command.o sls.o
	gcc -o main prompt.o main.o command.o sls.o

prompt.o : prompt.c
	gcc -c -o prompt.o prompt.c

command.o : command.c
	gcc -c -o command.o command.c

sls.o : sls.c
	gcc -c -o sls.o sls.c

main.o : main.c
	gcc -c -o main.o main.c



clean :
	rm *.o main
