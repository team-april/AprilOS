<<<<<<< HEAD
main : prompt.o main.o command.o sls.o
	gcc -o main prompt.o main.o command.o sls.o
=======
main : prompt.o main.o command.o cdr.o mkr.o
	gcc -o main prompt.o main.o command.o cdr.o mkr.o
>>>>>>> f7c49275b40ba632dce183e2676cf62d4aec06af

prompt.o : prompt.c
	gcc -c -o prompt.o prompt.c

command.o : command.c
	gcc -c -o command.o command.c

<<<<<<< HEAD
sls.o : sls.c
	gcc -c -o sls.o sls.c
=======
cdr.o : cdr.c
	gcc -c -o cdr.o cdr.c

mkr.o : mkr.c
	gcc -c -o mkr.o mkr.c
>>>>>>> f7c49275b40ba632dce183e2676cf62d4aec06af

main.o : main.c
	gcc -c -o main.o main.c



clean :
	rm *.o main
