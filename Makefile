#
# Makefile for the Spica C library.
#

CC=gcc
CCFLAGS=-Wall -c -O
check: CCFLAGS=-Wall -c -fprofile-arcs -ftest-coverage
debug: CCFLAGS=-Wall -g -O0 -c
LINK=ar
LINKFLAGS=rc
SOURCES=BitFile.c \
	hash.c        \
	Interval.c    \
	sema.c        \
	str.c         \
	ThreadPool.c  \
	Timer.c       \
	Tree.c        \
	Vector3.c     \
	WorkQueue.c
OBJECTS=$(SOURCES:.c=.o)
LIBRARY=libSpicaC.a

%.o:	%.c
	$(CC) $(CCFLAGS) $< -o $@

$(LIBRARY):	$(OBJECTS)
	$(LINK) $(LINKFLAGS) -o $@ $(OBJECTS)


check:	$(LIBRARY)

debug:	$(LIBRARY)

# File Dependencies
###################

# Module dependencies -- Produced with 'depend' on Mon Aug  7 23:10:42 2023


BitFile.o:	BitFile.c BitFile.h 

hash.o:	hash.c hash.h 

Interval.o:	Interval.c Interval.h 

sema.o:	sema.c sema.h 

str.o:	str.c str.h 

ThreadPool.o:	ThreadPool.c ThreadPool.h 

Timer.o:	Timer.c Timer.h environ.h 

Tree.o:	Tree.c Tree.h 

Vector3.o:	Vector3.c Vector3.h 

WorkQueue.o:	WorkQueue.c WorkQueue.h 


# Additional Rules
##################
clean:
	rm -f *.bc *.o $(LIBRARY) *.s *.ll *.gcov *.gcda *.gcno *~
