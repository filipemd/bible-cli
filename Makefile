UNAME_S := $(shell uname -s)

ifeq (UNAME_S, FreeBSD)
CC = clang
CXX = clang++
else
CC = gcc
CXX = g++
endif


QMAKE = qmake6

C_FLAGS = -Wall -Wextra -Wpedantic
CXX_FLAGS = -Wall -Wextra -Wpedantic
EXECUTABLE_NAME = bible
OPTIMIZATION_LEVEL = s

INCLUDE_PATH = 

THIRDPARTY_DIR = third-party

# Find all C files recursively under src directory
C_FILES := src/bible.c src/cli-main.c
# Find all C++ files recursively under src directory
CPP_FILES := src/main.cc

# Generate object file names for C and C++ files
C_OBJ_FILES := $(patsubst src/%.c, src/%.o, $(C_FILES))
CPP_OBJ_FILES := $(patsubst src/%.cc, src/%.o, $(CPP_FILES))

CLI = false

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
	$(MAKE) -C $(THIRDPARTY_DIR)/cJSON

gui:
	cd src/gui && $(QMAKE) . && $(MAKE)

install:
ifeq ($(UNAME_S), Darwin)
ifeq ($(CLI), true)
	cp $(EXECUTABLE_NAME) /usr/local/bin
else
	cp -r bible.app /Applications/
endif

	mkdir -p /usr/local/share/bible-cli/
	cp -r bible-json /usr/local/share/bible-cli/
else
	cp $(EXECUTABLE_NAME) /usr/bin/

	mkdir -p /usr/share/bible-cli/
	cp -r bible-json /usr/share/bible-cli/
endif

uninstall:
ifeq ($(UNAME_S), Darwin)
ifeq ($(CLI), true)
	rm /usr/local/bin/$(EXECUTABLE_NAME)
else
	rm -rf /Applications/bible.app
endif
	rm -rf  /usr/local/share/bible-cli/
else
	rm /usr/bin/$(EXECUTABLE_NAME)
	rm -rf  /usr/share/bible-cli/
endif

clean:
	rm -rf $(C_OBJ_FILES) $(CPP_OBJ_FILES) $(EXECUTABLE_NAME)
	$(MAKE) -C src/gui clean
	$(MAKE) -C $(THIRDPARTY_DIR)/cJSON clean

.PHONY: all clean cjson gui
