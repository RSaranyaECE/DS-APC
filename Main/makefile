SRCS := $(wildcard *.c)
TARGETS := $(SRCS:.c=.out)
LFLAG := -L ../Library  -lapc -ldlist
CFLAG := -I ../Include

all : ${TARGETS}

%.out : %.c
	gcc $^ ${LFLAG} ${CFLAG} -o $@

clean :
	rm ${TARGETS} 
	
