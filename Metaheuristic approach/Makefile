EXECUTABLE = test

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

MAIN = main
TS   = tabu_search
SOL  = solution

CC       = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic

OBJECTS = $(BIN_DIR)/$(MAIN).o \
          $(BIN_DIR)/$(TS).o \
          $(BIN_DIR)/$(SOL).o \

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(CPPFLAGS) -o $@

$(BIN_DIR)/$(MAIN).o: $(SRC_DIR)/$(MAIN).cpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@

$(BIN_DIR)/$(TS).o: $(SRC_DIR)/$(TS).cpp $(INC_DIR)/$(TS).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@
	
$(BIN_DIR)/$(SOL).o: $(SRC_DIR)/$(SOL).cpp $(INC_DIR)/$(SOL).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR):
	mkdir $@ -p

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)
