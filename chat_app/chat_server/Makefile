SRC_DIR=src
BIN_DIR=bin

CXX=g++
DEPFLAGS=-MP -MD
CXXFLAGS=-Wall -Werror -Wextra -Wshadow -pthread -pedantic-errors -std=c++17 -I . $(DEPFLAGS)
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

SRC=$(wildcard $(SRC_DIR)/*.cpp)
HDR=$(patsubst %.cpp, $(BIN_DIR)/%.d, $(notdir $(SRC)))
OBJ=$(patsubst %.cpp, $(BIN_DIR)/%.o, $(notdir $(SRC)))
BIN=$(BIN_DIR)/server

all: $(BIN)

debug: CXXFLAGS += -DDEBUG -ggdb
debug: $(BIN)

release: CXXFLAGS += -O2 -DNDEBUG
release: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	@rm -rf $(HDR) $(OBJ) $(BIN)

clean_o:
	@rm -rf .cache compile_commands.json
