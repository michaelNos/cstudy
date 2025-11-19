CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
OBJ = main.o wordcount.o
TARGET = wordcount

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c wordcount.h
	$(CC) $(CFLAGS) -c main.c

wordcount.o: wordcount.c wordcount.h
	$(CC) $(CFLAGS) -c wordcount.c

clean:
	rm -f $(OBJ) $(TARGET)