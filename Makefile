CC=gcc
CFLAGS=-Wall
CPPFLAGS=-Wall

OBJ=testsi.o test1.o snippets.o ConvertUTF.o

testsi:	$(OBJ)
	gcc -o testsi -lstdc++ $(OBJ)

clean:
	rm -f testsi $(OBJ)
