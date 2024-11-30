CC = gcc

CFLAGS = -std=c11 -Ilibs/include -Iinclude

SRC = libs/src/list.c \
	  src/main.c src/avl.c src/csv_parser.c src/csv_output.c \
	  src/application_settings.c src/result_generator.c src/maths.c \
	  src/application_test.c src/qsort.c

OBJ = $(SRC:.c=.o)

TARGET = CyEnedis

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)