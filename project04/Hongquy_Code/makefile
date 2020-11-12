CC = gcc
#CFLAGS = 

%.o : %.c
	$(CC) $< -o $@ $(CFLAGS)

clean :
	rm -rf *.o a.out

package :
	tar -cvzf proj-4.tar.gz TCB.h q.h threads.h sem.h msgs.h msgs_test.c
