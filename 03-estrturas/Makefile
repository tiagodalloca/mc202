CC=gcc
FLAGS=-std=c99 -pedantic -Wall -lm
BIN=prog
SOURCE=03-estruturas.c
INPUT_PATH=input
OUTPUT_PATH=output

build:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)

run:build
	./$(BIN) < $(INPUT_PATH)/arq1.in > $(OUTPUT_PATH)/arq1.out
	./$(BIN) < $(INPUT_PATH)/arq2.in > $(OUTPUT_PATH)/arq2.out

test:run
	-sdiff -s $(OUTPUT_PATH)/arq1.out $(OUTPUT_PATH)/arq1.res
	-sdiff -s $(OUTPUT_PATH)/arq2.out $(OUTPUT_PATH)/arq2.res

valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $(INPUT_PATH)/arq1.in > $(OUTPUT_PATH)/arq1.out
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $(INPUT_PATH)/arq2.in > $(OUTPUT_PATH)/arq2.out
