CC = gcc
AR = ar

CFLAGS = -Wall -ggdb3 -O8 -c -Iinclude
ARFLAGS = rcs
IFLAGS = -L$(BIN)/cc
OBJ = hcc
BIN = bin
SRC = src

OBJ-O = $(BIN)/tools.o $(BIN)/lexical.o $(BIN)/operfile.o

all: $(BIN)/main.o $(BIN)/libcc.a
	$(CC) $(IFLAGS) -o $(BIN)/$(OBJ) $<


$(BIN)/libcc.a: $(OBJ-O)
	$(AR) $(ARFLAGS) $@ $^

$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(BIN)/*.a $(BIN)/.o $(BIN)/$(OBJ)
