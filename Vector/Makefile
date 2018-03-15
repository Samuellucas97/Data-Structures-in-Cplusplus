RM = rm -rf 
CC=g++

INC_DIR=./include
SRC_DIR=./src
BIN_DIR=./bin
DOC_DIR=./doc
OBJ_DIR=./build

CFLAGS= -Wall -ansi -pedantic -std=c++11

.PHONY: all	clean	doxy	debug	doc

all: init exe 

debug: CFLAGS += -g -O0
debug: exe 

init:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

exe: CFLAGS+= -I$(INC_DIR)
exe: $(OBJ_DIR)/main.o $(OBJ_DIR)/vector.o
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel exe criado em $(BIN_DIR)] +++"
	@echo "============="

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(CFLAGS) -o $@ $<
$(OBJ_DIR)/vector.o:$(INC_DIR)/vector.h
	$(CC) -c $(CFLAGS) -o $@ $<

doxy:
	doxygen -g	

doc:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

clean:
	$(RM) $(BIN_DIR)
	$(RM) $(OBJ_DIR)

