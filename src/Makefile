main : prompt.o main.o command.o sls.o cdr.o mkr.o MAN.o chm.o pdr.o shw.o cpy.o del.o mov.o psl.o kil.o ech.o sta.o nfl.o
	gcc -o main prompt.o main.o command.o sls.o cdr.o mkr.o MAN.o chm.o pdr.o shw.o cpy.o del.o mov.o psl.o kil.o ech.o sta.o nfl.o
	rm *.o

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

cpy.o : cpy.c
	gcc -c -o cpy.o cpy.c

MAN.o : MAN.c
	gcc -c -o MAN.o MAN.c

chm.o : chm.c
	gcc -c -o chm.o chm.c

pdr.o : pdr.c
	gcc -c -o pdr.o pdr.c

shw.o : shw.c
	gcc -c -o shw.o shw.c

del.o : del.c
	gcc -c -o del.o del.c

mov.o : mov.c
	gcc -c -o mov.o mov.c

psl.o : psl.c
	gcc -c -o psl.o psl.c
	
kil.o : kil.c
	gcc -c -o kil.o kil.c

ech.o : ech.c
	gcc -c -o ech.o ech.c
	
sta.o : sta.c
	gcc -c -o sta.o sta.c

nfl.o : nfl.c
	gcc -c -o nfl.o nfl.c

main.o : main.c
	gcc -c -o main.o main.c



clean :
	rm *.o main
