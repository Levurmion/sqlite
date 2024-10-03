.PHONY: all

CXX := g++
CXXFLAGS := -Wall -std=c++17

CMD := $(CXX) $(CXXFLAGS)

# directories
OBJ := ./objects
SRC := ./src
BIN := ./bin

all: main.o argparser.o strings.o
	$(CMD) $(OBJ)/main.o $(OBJ)/argparser.o $(OBJ)/strings.o -o $(BIN)/sqlite-cpp

main.o:
	$(CMD) -c $(SRC)/main.cpp -o $(OBJ)/main.o

argparser.o:
	$(CMD) -c $(SRC)/argparser/argparser.cpp -o $(OBJ)/argparser.o

strings.o:
	$(CMD) -c $(SRC)/utils/strings.cpp -o $(OBJ)/strings.o