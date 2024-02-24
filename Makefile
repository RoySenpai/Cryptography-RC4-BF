# Use the gcc compiler.
CC = gcc

# Flags for the compiler.
CFLAGS = -std=c11 -I$(SOURCE_PATH)

# OS detection.
ifeq ($(OS),Windows_NT)
# Flags for the linker.
LDFLAGS = -lws2_32

# Remove command for Windows.
RM = del /Q /F /S

# Executable name.
EXECUTABLE = RC4_attack.exe
else
# Flags for the linker.
LDFLAGS = -pthread

# Remove command for Unix/Linux.
RM = rm -f

# Executable name.
EXECUTABLE = RC4_attack
endif

# Constants for the source, object and include paths.
SOURCE_PATH = sources
OBJECT_PATH = objects
INCLUDE_PATH = include

# Variables for the source, object and header files.
SOURCES = $(wildcard $(SOURCE_PATH)/*.c)
HEADERS = $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS = $(subst sources/,objects/,$(subst .c,.o,$(SOURCES)))

# Variable for the object files.
OBJECTS_RC4 = RC4_attack.o RC4_crypt.o RC4_utils.o RC4_rand.o
OBJ_FILES_RC4 = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_RC4))

# Phony targets - targets that are not files but commands to be executed by make.
.PHONY: all default clean

# Default target - compile everything and create the executables and libraries.
all: $(EXECUTABLE)

# Alias for the default target.
default: all


############
# Programs #
############
$(EXECUTABLE): $(OBJ_FILES_RC4)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

################
# Object files #
################
$(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	
#################
# Cleanup files #
#################
clean:
ifeq ($(OS),Windows_NT)
	$(RM) *.o $(EXECUTABLE)
else
	$(RM) $(OBJECT_PATH)/*.o $(EXECUTABLE)
endif
