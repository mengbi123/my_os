CROSS = riscv64-linux-gnu-
CC = $(CROSS)gcc
LD = $(CROSS)ld

CFLAGS = -march=rv64gc -mabi=lp64 -ffreestanding -nostdlib -Wall -Wextra
LDFLAGS = -T linker.ld

# build目录
BUILD_DIR = build

# 目标文件产物
OBJS = \
	$(BUILD_DIR)/entry.o \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/uart.o \
	$(BUILD_DIR)/print.o

# 默认目标
all: $(BUILD_DIR)/kernel.elf

# 确保 build 目录存在
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 编译规则
$(BUILD_DIR)/entry.o: kernel/entry.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: kernel/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(BUILD_DIR)/uart.o: kernel/uart.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(BUILD_DIR)/print.o: kernel/print.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# 链接规则
$(BUILD_DIR)/kernel.elf: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) $(OBJS) -o $@

run: $(BUILD_DIR)/kernel.elf
	qemu-system-riscv64 \
		-machine virt \
		-nographic \
		-kernel $(BUILD_DIR)/kernel.elf

clean:
	rm -rf $(BUILD_DIR)