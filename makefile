main: main.o
	gcc -g -o main main.o
main.o: main.c
	gcc -c -g main.c

clean:
	rm *.o main
