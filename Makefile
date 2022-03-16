CC = g++
FLAGS = -Wall -Wextra
OBJS = Meta3.o

# generic
all:		prog
clean:		clean
run:		run


# not generic at all
run:		prog
			./prog

prog:		$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o prog

clean:		$(OBJS)
			rm $(OBJS) prog

Meta3.o:	Meta3.cpp
			$(CC) $(FLAGS) -c Meta3.cpp

