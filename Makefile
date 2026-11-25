mypreprocessor: main.o comment_removal.o file_inclusion.o mystring.o macro_handler.o
	gcc main.o comment_removal.o file_inclusion.o mystring.o macro_handler.o -o mypreprocessor

main.o: main.c
	gcc -c main.c

comment_removal.o: comment_removal.c
	gcc -c comment_removal.c

file_inclusion.o: file_inclusion.c
	gcc -c file_inclusion.c

mystring.o: mystring.c
	gcc -c mystring.c

macro_handler.o: macro_handler.c
	gcc -c macro_handler.c

clean:
	rm -f *.o mypreprocessor
