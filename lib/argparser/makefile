include ../../common.mk

.PHONY: all

all: main

main: argparser.o main.o
	$(CMD) ./obj/argparser.o ./obj/main.o -o ./bin/main

main.o: main.cpp
	$(CMD) -o ./obj/main.o -c main.cpp

argparser.o: argparser.cpp
	$(CMD) -o ./obj/argparser.o -c argparser.cpp


