all: src/main.c 
	gcc -o trabalho2.exe src/main.c -Wall -Wextra -Wpedantic

exe: trabalho2.exe
	./trabalho2.exe

rm: trabalho2.exe
	rm trabalho2.exe