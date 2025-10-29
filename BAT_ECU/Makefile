USERNAME := $(shell whoami)
ifeq ($(USERNAME), lx)
    CC :=    /home/vmuser/AM35D1/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-gcc
	CXX :=   /home/vmuser/AM35D1/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-g++
	STRIP := /home/vmuser/AM35D1/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-strip
else ifeq ($(USERNAME), haozi)
    CC :=    /home/haozi/work/xcharge/toolchain/AM35D1/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-gcc
	CXX :=   /home/haozi/work/xcharge/toolchain/AM35D1/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-g++
	STRIP := /home/haozi/work/xcharge/toolchain/AM35D1/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-strip
else ifeq ($(USERNAME), stt)
    CC :=    /home/stt/arm/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-gcc
	CXX :=   /home/stt/arm/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-g++
	STRIP := /home/stt/arm/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-strip
else
    CC :=    /home/tian/tools/toolchainAM35/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-gcc
	CXX :=   /home/tian/tools/toolchainAM35/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-g++
	STRIP := /home/tian/tools/toolchainAM35/aarch64-nuvoton-linux-gnu_sdk-buildroot/bin/aarch64-nuvoton-linux-gnu-strip
endif

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# 指定交叉编译 sysroot 路径
SYSROOT := /home/stt/arm/aarch64-nuvoton-linux-gnu_sdk-buildroot/aarch64-buildroot-linux-gnu/sysroot
LIB_DIR := $(SYSROOT)/usr/lib
INC_DIR := $(SYSROOT)/usr/include

# 依赖的库
LIBS = -lwebsockets -ljson-c -lsqlite3 -lpthread -lssl -lcrypto -lzstd -lm -lzlog -lcurl

# 头文件包含路径（自动加源目录 + SYSROOT include）
INCLUDES = $(shell find $(SRC_DIR) -type d) $(INC_DIR)
CFLAGS = -Wall -O2 -MMD -MP $(addprefix -I, $(INCLUDES))
LDFLAGS = -L$(LIB_DIR) $(LIBS)

# 源文件与目标文件
SRCS = $(shell find $(SRC_DIR) -name '*.c' -type f)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/bat_ecu

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -g -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
