CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall

# Set the EXECUTABLE_NAME variable to the preferred generated executable name
# Set the SOURCES variable to a space-separated list of all the .cpp files to compile

EXECUTABLE_NAME = ./CreateGraphAndTest
EXECUTABLE_NAME2 = ./FindPaths
EXECUTABLE_NAME3 = ./TopologicalSort

SOURCES = CreateGraphAndTest.cpp
SOURCES2 = FindPaths.cpp
SOURCES3 = TopologicalSort.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS2 = $(SOURCES2:.cpp=.o)
OBJECTS3 = $(SOURCES3:.cpp=.o)



all: $(EXECUTABLE_NAME) $(EXECUTABLE_NAME2) $(EXECUTABLE_NAME3)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

$(EXECUTABLE_NAME2): $(OBJECTS2)
	$(CC) -o $(EXECUTABLE_NAME2) $(OBJECTS2)

$(EXECUTABLE_NAME3): $(OBJECTS3)
	$(CC) -o $(EXECUTABLE_NAME3) $(OBJECTS3)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)