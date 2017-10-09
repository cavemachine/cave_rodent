CC=gcc
CFLAGS=-I.
DEPS = cave_rodent.h
OBJ = cave_rodent.o movement.o entity.o 
LIBS = -lSDL2
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_alg: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o