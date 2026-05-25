all:
	gcc $(wildcard src/*.c src/*/*.c src/*/*/*.c) -o main.exe