#makefile for icalc.nasm
icalc: icalc.o
	gcc -o icalc icalc.o -no-pie
icalc.o: icalc.nasm
	nasm -f elf64 -g -F dwarf icalc.nasm -l icalc.lst
