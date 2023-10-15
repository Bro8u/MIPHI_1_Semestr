SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)
RESULT := main
SCRIPTS := $(wildcard *.sh)
SCRIPT_TARGETS := $(SCRIPTS:.sh=_run)

ifeq ($(OS), Windows_NT)
    USER_OS := Windows
else
    USER_OS := $(shell uname -s)
endif

ifneq ($(USER_OS), Darwin)
	ASAN_OPTIONS := detect_leaks=1
endif

OBJECTS := $(SOURCES:.cpp=.o)
CFLAGS := -g -fsanitize=address -std=c++2a -Wall -Werror
LDFLAGS := -fsanitize=address

all: run

run: compile
	ASAN_OPTIONS=$(ASAN_OPTIONS) ./$(RESULT)

%_run: %.sh
	/bin/bash $<

compile: $(RESULT) $(SCRIPT_TARGETS)


$(OBJECTS): %.o: %.cpp $(HEADERS)
	g++ $(CFLAGS) -c $< -o $@

$(RESULT): $(OBJECTS)
	g++ $(LDFLAGS) $(OBJECTS) -o $(RESULT)

clean:
	rm -f $(OBJECTS) $(RESULT)
