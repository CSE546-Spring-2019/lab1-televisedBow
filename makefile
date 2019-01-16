CC = gcc
CFLAGS = -Wall
DEPS = read.h
OBJ = count.o read.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

count: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	@rm -f $(PROGRAMS) *.o core
	rm count
