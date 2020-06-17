CC      = gcc
PROF    = -O0
C_FLAGS = -Wall -Wcast-align $(PROF)
L_FLAGS = $(PROF)
O_FILES = world.o

all: world
	$(CC) $(L_FLAGS) -ggdb3 -o world -pg

clean:
	rm -f world *.o
