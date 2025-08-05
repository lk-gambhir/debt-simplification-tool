# Makefile for Debt Simplification Tool
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executable
TARGET = debt_minimizer

# Source files
SOURCES = main.cpp debt_minimizer.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = debt_minimizer.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build completed successfully!"
	@echo "Run with: ./$(TARGET)"

# Compile object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean completed!"

# Install (copy to /usr/local/bin - requires sudo)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installed to /usr/local/bin/"

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstalled from /usr/local/bin/"

# Create sample input file
sample:
	@echo "alice bob 100" > sample_input.txt
	@echo "bob charlie 50" >> sample_input.txt
	@echo "charlie alice 30" >> sample_input.txt
	@echo "david alice 20" >> sample_input.txt
	@echo "bob david 10" >> sample_input.txt
	@echo "Sample input file 'sample_input.txt' created!"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Release build
release: CXXFLAGS += -DNDEBUG
release: $(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the executable (default)"
	@echo "  clean    - Remove build files"
	@echo "  run      - Build and run the program"
	@echo "  debug    - Build with debug information"
	@echo "  release  - Build optimized release version"
	@echo "  sample   - Create sample input file"
	@echo "  install  - Install to system (requires sudo)"
	@echo "  uninstall- Remove from system (requires sudo)"
	@echo "  help     - Show this help message"

.PHONY: all clean install uninstall sample run debug release help