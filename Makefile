# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source and Object Files
SRC = shell.c
OBJ = $(SRC:.c=.o)

# Executable Name
TARGET = myshell

# Default Target (Compiles Everything)
all: $(TARGET)

# Create Executable from Object Files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile .c Files into .o Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the Shell
run: $(TARGET)
	./$(TARGET)

# Clean Compiled Files
clean:
	rm -f $(OBJ) $(TARGET)
