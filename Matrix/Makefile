CFLAGS =
CC = gcc
SOURCES = ./source/Matrix.c ./functions/Dimention_read.c ./functions/Matrix_curl.c ./functions/Matrix_init.c ./functions/Matrix_output.c ./functions/Matrix_snake.c ./functions/Matrix_triangle_down.c ./functions/Matrix_triangle_up.c

OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE =  Matrix

all: exec

debug: CFLAGS += -g3
debug: clean
debug: exec

exec: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(CFLAGS)

.PHONY: clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -c $(OBJECTS) $@
