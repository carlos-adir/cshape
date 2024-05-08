# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall

# The name of the output file
OUTPUT = a.out

# Source files
SOURCES = test_nurbs.cpp nurbs.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Rule to build the final executable
$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Default rule
all: clean $(OUTPUT)

# Clean rule
clean:
	rm -f $(OBJECTS) $(OUTPUT)
