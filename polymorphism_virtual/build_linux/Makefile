CC=g++
CFLAG := -Wall -g -std=c++11

target=inside_object
SRCS= ../source/main.cpp

INC= -I../source/

OBJS=$(SRCS:.cpp=.o)

$(target):$(OBJS)
	$(CC) -o $@ $^

%.o:%.cpp
	$(CC) $(CFLAG) $(INC) -o $@ -c $<

.PHONY: clean
clean:
	-rm -rf *.o *.out
	-rm $(OBJS) $(target)

