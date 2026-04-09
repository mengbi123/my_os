CROSS = riscv64-linux-gnu-
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS = -march=rv64gc -mabi=lp64 -ffreestanding -nostdlib -Wall -Wextra
LDFLAGS = -T linker.ld

OBJS = \
	kernel/entry.o \
	kernel/main.o \
	kernel/uart.o

all: kernel.elf

kernel/entry.o: kernel/entry.S
	$(CC) $(CFLAGS) -c $< -o $@

kernel/main.o: kernel/main.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/uart.o: kernel/uart.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.elf: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) $(OBJS) -o $@

run: kernel.elf
	qemu-system-riscv64 \
		-machine virt \
		-nographic \
		-kernel kernel.elf

clean:
	rm -f kernel/*.o kernel.elf