CC = g++
FLAGS = -Wall -Wextra
OBJS = Solution1.o
.PHONY:	all clean

all:		prog

prog:		$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o prog

clean:		
			rm $(OBJS) prog

%.o:		%.c
			$(CC) $(FLAGS) $(OBJS) -c ^$


Solution.o:	Solution1.cpp