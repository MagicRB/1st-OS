TARGET=		i686-elf
CC=		$(TARGET)-gcc
CPP=		$(TARGET)-g++
AS=		$(TARGET)-as

C_FILES=	$(shell find src -type f -name '*.c')
H_FILES=	$(shell find include -type f -name '*.h')
S_FILES=	$(shell find asm -type f -name '*.s')

OBJ= 		$(C_FILES:.c=.o) $(S_FILES:.s=.o)

default: $(OBJ)
	$(CC) -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib $(OBJ) -lgcc
%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@ -ffreestanding -std=gnu99 -g -I include

run-qemu: os.bin
	qemu-system-i386 -kernel os.bin

clean:
	rm -f $(OBJ) os.bin
