CC = gcc
#CFLAGS = 

%.o : %.c
	$(CC) $< -o $@ $(CFLAGS)

clean :
	rm -rf *.o a.out

package :
	tar -cvzf proj-3.tar.gz TCB.h q.h threads.h sem.h read_write.c
