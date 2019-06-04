main : prompt.o main.o cdr.o
	gcc -o main prompt.o main.o cdr.o

prompt.o : prompt.c
	gcc -c -o prompt.o prompt.c

cdr.o : cdr.c
	gcc -c -o cdr.o cdr.c

main.o : main.c
	gcc -c -o main.o main.c

clean :
	rm *.o main
