include common.mk

.PHONY: all clean

GEN_OBJECT := $(CMD) -c $^ -o $@
OBJECTS := $(OBJ)/main.o $(OBJ)/argparser.o $(OBJ)/strings.o

all: $(OBJECTS)

clean:
	rm -f $(OBJ)/*.o

main: $(OBJECTS)
	$(CMD) $^ -o $(BIN)/$@

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CMD) -c $^ -o $@

$(OBJ)/argparser.o: $(LIB)/argparser/argparser.cpp
	$(CMD) -c $^ -o $@

$(OBJ)/strings.o: $(LIB)/utils/strings.cpp
	$(CMD) -c $^ -o $@


# $^: Expands to all the prerequisites (i.e., ./obj/argparser.o ./obj/main.o).
# $@: The current target (e.g., ./obj/main.o).
# $<: The first prerequisite (e.g., main.cpp or argparser.cpp).