SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
BIN_NAME = tower_def

CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o TileMap.o Tile.o MenuScreen.o

all: make_build_dir $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(LFLAGS) $(BUILD_DIR)/*.o -o $(BIN_DIR)/$(BIN_NAME) 

main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

TileMap.o: $(SRC_DIR)/TileMap.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/TileMap.cpp -o $(BUILD_DIR)/TileMap.o
	
Tile.o: $(SRC_DIR)/Tile.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/Tile.cpp -o $(BUILD_DIR)/Tile.o
	
MenuScreen.o: $(SRC_DIR)/MenuScreen.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/MenuScreen.cpp -o $(BUILD_DIR)/MenuScreen.o

make_build_dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	
