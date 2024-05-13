CC = gcc
CXX = g++

QMAKE = qmake|qmake6

C_FLAGS = -Wall -Wextra -Wpedantic
CXX_FLAGS = -Wall -Wextra -Wpedantic
EXECUTABLE_NAME = bible
OPTIMIZATION_LEVEL = s

INCLUDE_PATH = 

THIRDPARTY_DIR = third-party

CLI = false

# Find all C files recursively under src directory
C_FILES := src/bible.c src/cli-main.c
# Find all C++ files recursively under src directory
CPP_FILES := src/main.cc

# Generate object file names for C and C++ files
C_OBJ_FILES := $(patsubst src/%.c, src/%.o, $(C_FILES))
CPP_OBJ_FILES := $(patsubst src/%.cc, src/%.o, $(CPP_FILES))

ifeq ($(CLI), true)
all: cjson $(EXECUTABLE_NAME)
else
all: cjson gui
endif

src/%.o: src/%.c
	$(CC) -c $< -o $@ $(C_FLAGS) -I$(THIRDPARTY_DIR) -O$(OPTIMIZATION_LEVEL) -DCLI

src/%.o: src/%.cc
	$(CXX) -c $< -o $@ $(CXX_FLAGS) -I$(THIRDPARTY_DIR) -O$(OPTIMIZATION_LEVEL) -DCLI

$(EXECUTABLE_NAME): $(C_OBJ_FILES) $(CPP_OBJ_FILES)
	$(CXX) $(C_OBJ_FILES) $(CPP_OBJ_FILES) $(THIRDPARTY_DIR)/cJSON/libcjson.a -o $@ $(CXX_FLAGS) -O$(OPTIMIZATION_LEVEL)

cjson:
	make -C $(THIRDPARTY_DIR)/cJSON

gui:
	cd src/gui && qmake . && make

clean:
	rm -rf $(C_OBJ_FILES) $(CPP_OBJ_FILES) $(EXECUTABLE_NAME)
	$(MAKE) -C src/gui clean
	$(MAKE) -C $(THIRDPARTY_DIR)/cJSON clean

.PHONY: all clean cjson gui
