CC = gcc
BUILD_COMMAND = build
SOURCES = new.c
REMOVE_TARGET = new.exe
OUTPUT_FILE = new
FLAGS = -Wall

# Build the target
$(BUILD_COMMAND): $(SOURCES)
	$(CC) $(FLAGS) $(SOURCES) -o $(OUTPUT_FILE)

# Clean target to remove compiled files
clean:
	del $(REMOVE_TARGET)

run:
	./$(OUTPUT_FILE)

