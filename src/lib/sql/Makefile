include ../../../common.mk

bin/main: obj/lexer.o obj/main.o
	$(CMD) $^ -o $@

obj/main.o: main.cpp
	$(CMD) -c $^ -o $@

obj/lexer.o: lexer.cpp
	$(CMD) -c $^ -o $@
