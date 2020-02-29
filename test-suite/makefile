

CC = g++
FLAGS = -std=c++11 

SOURCES := $(wildcard t*.cpp)

EXECUTABLES = $(SOURCES:.cpp=)

all: $(EXECUTABLES)

% : %.cpp TravelOptions.h _to_util.h
	$(CC) $(FLAGS)  $< -o $@

clean:
	rm -f $(EXECUTABLES)

