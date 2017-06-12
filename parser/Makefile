CC = clang
CFLAGS = -g
#DEBUG = -DBINARYDEBUG

SRCS = lib/linkedlist.o main.c lib/talloc.o lib/tokenizer.o parser.c
HDRS = linkedlist.h value.h talloc.h tokenizer.h parser.h
OBJS = $(SRCS:.c=.o)

parser: $(OBJS)
	$(CC)  -rdynamic $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) $(DEBUG) -c $<  -o $@

clean:
	rm *.o
	rm parser

