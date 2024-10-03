include ../../common.mk

.PHONY: all

all: main

main: argparser.o main.o
	$(CMD) ./obj/argparser.o ./obj/main.o -o ./bin/main

main.o:
	$(CMD) -o ./obj/main.o -c main.cpp

argparser.o:
	$(CMD) -o ./obj/argparser.o -c argparser.cpp


# $^: Expands to all the prerequisites (i.e., ./obj/argparser.o ./obj/main.o).
# $@: The current target (e.g., ./obj/main.o).
# $<: The first prerequisite (e.g., main.cpp or argparser.cpp).