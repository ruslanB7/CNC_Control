
TARGET = prog
LIBS = -lm -lncursesw
CC = gcc
CFLAGS = -g -Wall

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: default all clean run

default: $(TARGET)
all: default


%.o: %.c $(HEADERS)
	@echo make $@
	@$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	@echo make $@
	@$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	@echo remove all
	@-rm -f *.o
	@-rm -f $(TARGET)
	@echo


run: $(TARGET)
	echo $(TARGET)
	./$(TARGET)
