include ../../../common.mk

.PHONY: clean

bin/main: obj/lexer.o obj/main.o obj/parser.o obj/non-terminals.o
	$(CMD) $^ -o $@

obj/main.o: main.cpp
	$(CMD) -c $^ -o $@

obj/lexer.o: lexer.cpp
	$(CMD) -c $^ -o $@

obj/parser.o: parser.cpp
	$(CMD) -c $^ -o $@

obj/non-terminals.o: non-terminals.cpp
	$(CMD) -c $^ -o $@

clean:
	rm -rf *.o
