CC=gcc
AR=ar
OBJECT_FREQUENCY=frequency.o
FLAGS = -Wall -g

all: main

main: frequencymain 

frequencymain:  $(OBJECT_FREQUENCY) frequency
	     $(CC) $(FLAGS) -o frequency libfrequency.a 

frequency: libfrequency.a
libfrequency.a: $(OBJECT_FREQUENCY)
	 $(AR) -rcs libfrequency.a $(OBJECT_FREQUENCY) 

frequency.o: frequency.c
	 $(CC) $(FLAGS) -c -fPIC frequency.c

.PHONY: 
	all clean main frequency
clean: 
	 rm -rf *.o *.a main 