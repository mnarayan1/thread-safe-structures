CC      = gcc
CFLAGS  = -g
RM      = rm -f
SRC_DIR = src
INC_DIR = include

default: all

all: queue

# Add the header file as a dependency
queue: $(SRC_DIR)/queue.c $(INC_DIR)/queue.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -o queue $(SRC_DIR)/queue.c

clean:
	$(RM) queue