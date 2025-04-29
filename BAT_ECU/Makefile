
CC = /home/len/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-linux-gcc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

INCLUDES = $(shell find $(SRC_DIR) -type d) 
CFLAGS = -Wall -Wextra -O2 -MMD -MP $(addprefix -I, $(INCLUDES))

SRCS = $(shell find $(SRC_DIR) -name '*.c' -type f)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/bat_ecu

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -lm -lzlog

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

