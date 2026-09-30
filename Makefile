CC = gcc
CFLAGS = -Wall -Wextra
RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC = src/*.c
OUT = app

all: $(OUT)

$(OUT): $(SRC)
	@bear -- $(CC) $(CFLAGS) $(RAYLIB) $(SRC) -o $(OUT)

clean:
	@rm $(OUT)

.PHONY: all clean
