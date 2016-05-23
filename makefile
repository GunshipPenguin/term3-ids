SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
BIN_NAME = tower_def

CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml2

OBJS = $(addprefix $(BUILD_DIR)/,main.o Tile.o MenuScreen.o GameScreen.o ResourceManager.o Logger.o Drawable.o Creep.o Updateable.o Path.o)

all: binary

binary: make_build_dir $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(LFLAGS) $(BUILD_DIR)/*.o -o $(BIN_DIR)/$(BIN_NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

make_build_dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)

