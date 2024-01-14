EXECUTABLE = test
MAIN = main
GENERATE = generate
CPPFLAGS = -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(MAIN).o $(GENERATE).o
	g++ $^ -o $@

$(MAIN).o: $(MAIN).cpp $(GENERATE).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

$(GENERATE).o: $(GENERATE).cpp $(GENERATE).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) *.o *.~

