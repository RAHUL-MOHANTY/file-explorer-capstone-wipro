CXX = g++
CXXFLAGS = -std=c++17 -O2
SRC = src/file_explorer.cpp
BIN = file_explorer

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
