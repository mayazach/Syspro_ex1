OBJS	= werhauz.o functions.o heap.o hash1.o hash2.o list1.o list2.o
SOURCE	= werhauz.c functions.c heap.c hash1.c hash2.c list1.c list2.c
HEADER	= functions.h heap.h hash1.h hash2.h list1.h list2.h
OUT	= werhauz
CC	= gcc
FLAGS	= -c -g

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

werhauz.o: werhauz.c
	$(CC) $(FLAGS) werhauz.c

functions.o: functions.c
	$(CC) $(FLAGS) functions.c

heap.o: heap.c
	$(CC) $(FLAGS) heap.c

hash1.o: hash1.c
	$(CC) $(FLAGS) hash1.c

hash2.o: hash2.c
	$(CC) $(FLAGS) hash2.c

list1.o: list1.c
	$(CC) $(FLAGS) list1.c

list2.o: list2.c
	$(CC) $(FLAGS) list2.c

clean:
	rm -f $(OBJS)
