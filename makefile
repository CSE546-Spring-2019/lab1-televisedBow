CC = gcc
CFLAGS = -Wall
DEPS = read.h
OBJ = main.o read.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	@rm -f $(PROGRAMS) *.o core