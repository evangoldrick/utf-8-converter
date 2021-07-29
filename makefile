CC = gcc

all: cpToHex hexToCp

cpToHex: cpToHex.o hexConversions.o
	$(CC) -g -o cpToHex cpToHex.o hexConversions.o

hexToCp: hexToCp.o hexConversions.o
	$(CC) -g -o hexToCp hexToCp.o hexConversions.o

cpToHex.o: cpToHex.c
	$(CC) -c -g cpToHex.c

hexToCp.o: hexToCp.c
	$(CC) -c -g hexToCp.c

hexConversions.o: hexConversions.c
	$(CC) -c -g hexConversions.c

clean:
	rm *.o cpToHex hexToCp
