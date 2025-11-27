CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude

OBJ=src/main.o src/cli.o src/dynarray.o src/io.o

all: kpi
kpi: $(OBJ)
	$(CC) $(CFLAGS) -o kpi $(OBJ)

clean:
	rm -f $(OBJ) kpi
