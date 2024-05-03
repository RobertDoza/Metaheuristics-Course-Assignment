EXECUTABLE = test

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

MAIN   = main
TS     = tabu_search
SOL    = solution
RANDOM = random
LOGGER = logger
INPUT  = input_reader
MODEL  = model

CC       = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic

OBJECTS = $(BIN_DIR)/$(MAIN).o \
          $(BIN_DIR)/$(TS).o \
          $(BIN_DIR)/$(SOL).o \
          $(BIN_DIR)/$(RANDOM).o \
          $(BIN_DIR)/$(LOGGER).o \
          $(BIN_DIR)/$(INPUT).o \
          $(BIN_DIR)/$(MODEL).o \

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(CPPFLAGS) -o $@

$(BIN_DIR)/$(MAIN).o: $(SRC_DIR)/$(MAIN).cpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(TS).o: $(SRC_DIR)/$(TS).cpp $(INC_DIR)/$(TS).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)
	
$(BIN_DIR)/$(SOL).o: $(SRC_DIR)/$(SOL).cpp $(INC_DIR)/$(SOL).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(RANDOM).o:	$(SRC_DIR)/$(RANDOM).cpp $(INC_DIR)/$(RANDOM).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(LOGGER).o:	$(SRC_DIR)/$(LOGGER).cpp $(INC_DIR)/$(LOGGER).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(INPUT).o: $(SRC_DIR)/$(INPUT).cpp $(INC_DIR)/$(INPUT).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(MODEL).o: $(SRC_DIR)/$(MODEL).cpp $(INC_DIR)/$(MODEL).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR):
	mkdir $@ -p

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)
