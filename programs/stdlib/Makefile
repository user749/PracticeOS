FILES=./build/start.o ./build/practiceos.o
INCLUDES=

all: ${FILES}
	i686-elf-ld -m elf_i386 -relocatable ${FILES} -o ./stdlib.elf

./build/start.o: ./src/start.asm
	nasm -f elf ./src/start.asm -o ./build/start.o

./build/practiceos.o: ./src/practiceos.asm
	nasm -f elf ./src/practiceos.asm -o ./build/practiceos.o

clean:
	rm -rf ${FILES}
	rm ./stdlib.elf