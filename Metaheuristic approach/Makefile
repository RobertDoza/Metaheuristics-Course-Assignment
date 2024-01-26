EXECUTABLE = test

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

MAIN = main
TS   = tabu_search

CC       = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic

OBJECTS = $(BIN_DIR)/$(MAIN).o $(BIN_DIR)/$(TS).o

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(CPPFLAGS) -o $@

$(BIN_DIR)/$(MAIN).o: $(SRC_DIR)/$(MAIN).cpp
	$(CC) $< -c $(CPPFLAGS) -o $@

$(BIN_DIR)/$(TS).o: $(SRC_DIR)/$(TS).cpp $(INC_DIR)/$(TS).hpp
	$(CC) $< -c $(CPPGLAGS) -o $@

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)
