CC = gcc
CXX = g++
C_FLAGS = -Wall -Wextra
CXX_FLAGS = -Wall -Wextra --std=c++17
C_LIBS =
CXX_LIBS = $(shell pkg-config gtkmm-4.0 --cflags --libs)
EXECUTABLE_NAME = bible
OPTIMIZATION_LEVEL = s
CJSON_DIR = third-party/cJSON

# Find all C files recursively under src directory
C_FILES := $(shell find src -type f -name '*.c')
# Find all C++ files recursively under src directory
CPP_FILES := $(shell find src -type f -name '*.cc')

# Generate object file names for C and C++ files
C_OBJ_FILES := $(patsubst src/%.c, src/%.o, $(C_FILES))
CPP_OBJ_FILES := $(patsubst src/%.cc, src/%.o, $(CPP_FILES))

all: cjson $(EXECUTABLE_NAME)

src/%.o: src/%.c
	$(CC) -c $< -o $@ $(C_FLAGS) -I$(CJSON_DIR) $(C_LIBS) -O$(OPTIMIZATION_LEVEL)

src/%.o: src/%.cc
	$(CXX) -c $< -o $@ $(CXX_FLAGS) -I$(CJSON_DIR) $(CXX_LIBS) -O$(OPTIMIZATION_LEVEL)

$(EXECUTABLE_NAME): $(C_OBJ_FILES) $(CPP_OBJ_FILES)
	$(CXX) $^ $(CJSON_DIR)/libcjson.a -o $@ $(CXX_FLAGS) $(C_LIBS) $(CXX_LIBS) -O$(OPTIMIZATION_LEVEL)

cjson:
	make -C $(CJSON_DIR)

clean:
	rm -rf $(C_OBJ_FILES) $(CPP_OBJ_FILES) $(EXECUTABLE_NAME)
	$(MAKE) -C $(CJSON_DIR) clean

.PHONY: all clean cjson
