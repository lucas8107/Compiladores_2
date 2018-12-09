
OBJS=scanner.o parser.o ast.o compiler.o
INTERM=scanner.c parser.c parser.h
PROGRAM=./compiler 
CFLAGS=-g

all: $(PROGRAM)

scanner.c: scanner.flex parser.h
	flex -o scanner.c scanner.flex

parser.c parser.h: parser.bison
	bison --defines=parser.h -o parser.c parser.bison

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS) $(INTERM)

test: $(PROGRAM)
	$(PROGRAM) test/test_factorial
	$(PROGRAM) test/test_fibonacci
	$(PROGRAM) test/test_if
	$(PROGRAM) test/test_if_else
	$(PROGRAM) test/test_while
