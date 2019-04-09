CC=g++
CFLAG := -Wall -g -std=c++11
OPT=-fno-elide-constructors

target=inside_object
target_no_optimized=inside_object_no_opt
SRCS= ../source/main.cpp

INC= -I../source/

OBJS=$(SRCS:.cpp=.o)

$(target):$(OBJS)
	$(CC) -o $@ $^

%.o:%.cpp
	$(CC) $(CFLAG) $(INC) -o $@ -c $<

# close compiler optimized option
no_opt:$(OBJS)
	$(CC) $(OPT) -o $(target_no_optimized) $^

.PHONY: clean
clean:
	-rm -rf *.o *.out
	-rm $(OBJS) $(target)

