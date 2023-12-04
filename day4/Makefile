# Define compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++20 #-Wall

# Get all .cpp files in the directory
SRCS := $(wildcard *.cpp)
# Generate list of corresponding executables
EXECS := $(SRCS:.cpp=)

# Target that generates executables for each source file
all: $(EXECS)

# Rule to generate executable from source file
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean rule
clean:
	rm -f $(EXECS)