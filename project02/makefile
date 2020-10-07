CC = gcc
#CFLAGS = 

%.o : %.c
	$(CC) $< -o $@ $(CFLAGS)

clean :
	rm -rf *.o

package :
	tar -cvzf proj-2.zip TCB.h q.h threads.h thread_test.c
