CC := gcc
TARGET := main.exe
SOURCES := $(wildcard src/*.c src/*/*.c src/*/*/*.c)

.PHONY: all build test clean

all: build

build:
	$(CC) $(SOURCES) -o $(TARGET)

test: build
	.\$(TARGET)

clean:
	-cmd /C "if exist $(TARGET) del /Q $(TARGET)"
	-cmd /C "if exist *.o del /Q *.o"
	-cmd /C "if exist build rmdir /S /Q build"
	-cmd /C "if exist bin rmdir /S /Q bin"
	-cmd /C "if exist obj rmdir /S /Q obj"
	-cmd /C "if exist out rmdir /S /Q out"
