all:
	gcc -Wall -g -o ArvoreAVL.o -c ArvoreAVL.c
	gcc -Wall -g -o main.o -c main.c
	gcc -Wall -g -o result main.o ArvoreAVL.o

run:
	./result

clean:
	del *.o

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./result