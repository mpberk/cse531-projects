CC = gcc
#CFLAGS = 

%.o : %.c
	$(CC) $< -o $@ $(CFLAGS)

clean :
	rm -rf *.o a.out

package :
	tar -cvzf proj-2.tar.gz TCB.h q.h threads.h thread_test.c
