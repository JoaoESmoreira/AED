CC = g++
FLAGS = -Wall -Wextra
OBJS = Meta2.o
.PHONY: all clean

# generic
all:		prog


# not generic at all
run:		prog
			./prog

prog:		$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o prog

clean:		$(OBJS)
			rm $(OBJS) prog

%.o:		%.cpp
			$(CC) $(FLAGS) -c $^
