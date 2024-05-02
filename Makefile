CC = gcc
C_FLAGS = -Wall -Wextra $(shell pkg-config --cflags gtk4)
C_LIBS = $(shell pkg-config --libs gtk4)
EXECUTABLE_NAME = bible
OPTIMIZATION_LEVEL = s
CJSON_DIR = third-party/cJSON

C_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c,src/%.o,$(C_FILES))

all: cjson $(EXECUTABLE_NAME)

src/%.o: src/%.c
	$(CC) -c $< -o $@ $(C_FLAGS) -I$(CJSON_DIR) -O$(OPTIMIZATION_LEVEL)

$(EXECUTABLE_NAME): $(OBJ_FILES)
	$(CC) $^ $(CJSON_DIR)/libcjson.a -o $@ $(C_FLAGS) $(C_LIBS) -I$(CJSON_DIR) -O$(OPTIMIZATION_LEVEL)

cjson:
	make -C $(CJSON_DIR)

clean:
	rm -rf src/*.o $(EXECUTABLE_NAME)
	$(MAKE) -C $(CJSON_DIR) clean

.PHONY: all clean cjson
