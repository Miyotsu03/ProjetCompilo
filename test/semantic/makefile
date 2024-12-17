CC = gcc
CFLAGS = -Wall -I$(INCDIR) -g

HOMEDIR = ../..
INCDIR = $(HOMEDIR)/include
SRCDIR = $(HOMEDIR)/src
OBJDIR = $(HOMEDIR)/obj

BIN = semantic_test

all: $(BIN)

.PHONY: all test clean

$(BIN): $(INCDIR)/semantic.h semantic_test.c $(OBJDIR)/semantic.o $(OBJDIR)/ast.o $(OBJDIR)/codegen.o $(OBJDIR)/ts.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

test:
	./$(BIN)

clean:
	rm -f *~ 
