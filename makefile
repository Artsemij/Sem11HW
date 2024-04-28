CC = gcc

CFLAGS = -Wall

SRCS = main.c temp_functions.c

OBJS = $(SRCS:.c=.o)

EXEC = temp_stat.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del -rf *.i *.s *.o *.exe

.PHONY: all clean