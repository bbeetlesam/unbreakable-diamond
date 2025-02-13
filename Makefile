# Compiler
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -IC:/_assets/lib/SFML3.0.0/include -I./inc -LC:/_assets/lib/SFML3.0.0/lib
LINK = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

# Directories
BIN_DIR = bin
OBJ_DIR = lib/obj
SRC_DIR = src
INC_DIR = inc
LIB_DIR = lib

# Source codes
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.hpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
LIBS = $(LIB_DIR)/libgame.a

# Target output binary
TARGET = $(BIN_DIR)/game.exe

# Target rules
all: $(TARGET)

# Final executable
$(TARGET): $(LIBS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LINK) -L$(LIB_DIR) -lgame

# Compile static library (.a) from object files
$(LIBS): $(OBJS)
	ar rcs $@ $^

# Compile all object (.o) files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/*.hpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run file exe
run: $(TARGET)
	./$(TARGET)

# Clean all object files
clean:
	rm -rf $(BIN_DIR)/*.exe $(OBJ_DIR)/*.o $(LIBS)


# # Compile exe
# $(TARGET): $(SRCS) $(HEADERS)
# 	$(CC) $(CFLAGS) $(SRCS) $(LINK) -o $(TARGET)