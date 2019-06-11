main : prompt.o main.o 
	gcc -o main prompt.o main.o 

prompt.o : prompt.c
	gcc -c -o prompt.o prompt.c


main.o : main.c
	gcc -c -o main.o main.c

clean :
	rm *.o main
