CC = gcc
CFLAGS = -lpthread

%.o : %.c
	$(CC) $< -o $@ $(CFLAGS)

clean :
	rm -rf *.o
