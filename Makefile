# Flags for the compiler and linker.
CC = gcc
CFLAGS = -std=c11 -g
RM = rm -f

# Phony targets - targets that are not files but commands to be executed by make.
.PHONY: all default clean

# Default target - compile everything and create the executables and libraries.
all: RC4_attack

# Alias for the default target.
default: all


############
# Programs #
############
RC4_attack: RC4_attack.o
	$(CC) $(CFLAGS) -pthread -o $@ $<

################
# Object files #
################
%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
#################
# Cleanup files #
#################
clean:
	$(RM) *.o *.so RC4_attack