CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
SRC = $(wildcard src/*.c)
EXEC = cfit

all: $(EXEC)

$(EXEC): $(SRC) src/*.h
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC) $(EXEC).exe
