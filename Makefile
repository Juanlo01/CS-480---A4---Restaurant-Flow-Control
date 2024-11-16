# Name: Juan Cota
# Date: 11/15/2024
# Red ID: 827272362

# Makefile

# Specify compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall -g3 -c

# Object files
OBJS = main.o producer.o consumer.o shared_queue.o log.o

# Program name
PROGRAM = dineseating

# This program depends on its object files
$(PROGRAM) : $(OBJS)
	$(CC) -pthread -o $(PROGRAM) $(OBJS)

main.o : main.c
	$(CC) $(CFLAGS) main.c

producer.o : producer.c producer.h
	$(CC) $(CFLAGS) producer.c

consumer.o : consumer.c consumer.h
	$(CC) $(CFLAGS) consumer.c

shared_queue.o : shared_queue.c shared_queue.h
	$(CC) $(CFLAGS) shared_queue.c

log.o : log.c log.h seating.h
	$(CC) $(CFLAGS) log.c

# Once things work, people frequently delete their object files.
# If you use "make clean", this will do it for you.
# As we use gnuemacs which leaves auto save files termintating
# with ~, we will delete those as well.
clean :
	rm -rf $(OBJS) *~ $(PROGRAM)

