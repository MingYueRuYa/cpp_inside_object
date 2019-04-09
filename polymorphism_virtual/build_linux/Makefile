# make opt=optimized no_opt 关闭编译器的优化选项
opt=
CC=g++
CFLAG := -Wall -g -std=c++11
ifeq ($(opt), optimized)
OPT := -fno-elide-constructors
else
OPT:= 
endif

target=inside_object
target_no_optimized=inside_object_no_opt
SRCS=../source/main.cpp

INC= -I../source/

OBJS=$(SRCS:.cpp=.o)

$(target):$(OBJS)
	$(CC) -o $@ $^

%.o:%.cpp
	$(CC) $(OPT) $(CFLAG) $(INC) -o $@ -c $<

# close compiler optimized option
#no_opt:$(OBJS)
#	$(CC) $(OPT) -o $(target_no_optimized) $^

.PHONY: clean
clean:
	rm -rf *.o *.out
	rm $(OBJS) $(target) $(target_no_optimized)

