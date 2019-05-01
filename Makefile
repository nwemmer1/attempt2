# Mention default target
program = seamCarving435
program-objects = seamCarving435.o

.PHONY: all
all: seamCarving435

seamCarving435: seamCarving435.o
	g++ --std=gnu++11 -o seamCarving435 seamCarving435.o

seamCarving435.o: seamCarving435.cc
	g++ --std=gnu++11 -c seamCarving435.cc

.PHONY: clean
clean:
	rm seamCarving435.o seamCarving435
