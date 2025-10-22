EXECUTABLE = test

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

MAIN   = main
TS     = tabu_search
TL     = tabu_list
SOL    = solution
MOV    = movement
NEITER = neighbor_iterator
RANDOM = random
LOGGER = logger
INPUT  = input_reader
MODEL  = model
UTILS  = utils
TIMER  = timer
PARAMS = parameters
STATS  = statistics

CC       = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic

OBJECTS = $(BIN_DIR)/$(MAIN).o \
          $(BIN_DIR)/$(TS).o \
		  $(BIN_DIR)/$(TL).o \
          $(BIN_DIR)/$(SOL).o \
          $(BIN_DIR)/$(MOV).o \
		  $(BIN_DIR)/$(NEITER).o \
          $(BIN_DIR)/$(RANDOM).o \
          $(BIN_DIR)/$(LOGGER).o \
          $(BIN_DIR)/$(INPUT).o \
          $(BIN_DIR)/$(MODEL).o \
          $(BIN_DIR)/$(UTILS).o \
          $(BIN_DIR)/$(TIMER).o \
          $(BIN_DIR)/$(PARAMS).o \
          $(BIN_DIR)/$(STATS).o \

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(CPPFLAGS) -o $@

$(BIN_DIR)/$(MAIN).o: $(SRC_DIR)/$(MAIN).cpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(TS).o: $(SRC_DIR)/$(TS).cpp $(INC_DIR)/$(TS).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(TL).o: $(SRC_DIR)/$(TL).cpp $(INC_DIR)/$(TL).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)
	
$(BIN_DIR)/$(SOL).o: $(SRC_DIR)/$(SOL).cpp $(INC_DIR)/$(SOL).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)
	
$(BIN_DIR)/$(MOV).o: $(SRC_DIR)/$(MOV).cpp $(INC_DIR)/$(MOV).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)
	
$(BIN_DIR)/$(NEITER).o: $(SRC_DIR)/$(NEITER).cpp $(INC_DIR)/$(NEITER).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(RANDOM).o:	$(SRC_DIR)/$(RANDOM).cpp $(INC_DIR)/$(RANDOM).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(LOGGER).o:	$(SRC_DIR)/$(LOGGER).cpp $(INC_DIR)/$(LOGGER).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(INPUT).o: $(SRC_DIR)/$(INPUT).cpp $(INC_DIR)/$(INPUT).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(MODEL).o: $(SRC_DIR)/$(MODEL).cpp $(INC_DIR)/$(MODEL).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(UTILS).o: $(SRC_DIR)/$(UTILS).cpp $(INC_DIR)/$(UTILS).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(TIMER).o: $(SRC_DIR)/$(TIMER).cpp $(INC_DIR)/$(TIMER).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(PARAMS).o: $(SRC_DIR)/$(PARAMS).cpp $(INC_DIR)/$(PARAMS).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR)/$(STATS).o: $(SRC_DIR)/$(STATS).cpp $(INC_DIR)/$(STATS).hpp | $(BIN_DIR)
	$(CC) $< -c $(CPPFLAGS) -o $@ -I$(INC_DIR)

$(BIN_DIR):
	mkdir $@ -p

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)
