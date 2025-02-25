CXX = g++
CXXFLAGS = -Wall -g -Werror -std=c++17
LDFLAGS = `pkg-config --libs --static glfw3 glew`

SRC = src
OBJ = obj
BIN = bin

SRCS = $(wildcard $(SRC)/*.cc)
OBJS = $(addprefix $(OBJ)/, $(patsubst %.cc,%.o,$(notdir $(SRCS))))
DEPS = $(OBJS:%.o=%.d)

TARGET_NAME = gloom
TARGET = $(BIN)/$(TARGET_NAME)
TARGET_ARGS = ./assets/doom.wad

$(TARGET): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $(TARGET)

$(OBJ)/%.o: $(SRC)/%.cc
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(DEPS)

.PHONY: run
run: $(TARGET)
	./$(TARGET) $(TARGET_ARGS)

.PHONY: clean
clean:
	rm $(OBJ)/* $(BIN)/*
