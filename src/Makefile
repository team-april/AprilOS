main : prompt.o main.o command.o 
	gcc -o main prompt.o main.o command.o 

prompt.o : prompt.c
	gcc -c -o prompt.o prompt.c

command.o : command.c
	gcc -c -o command.o command.c

main.o : main.c
	gcc -c -o main.o main.c



clean :
	rm *.o main
