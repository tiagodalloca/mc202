CC=gcc
FLAGS=-std=c99 -pedantic -Wall -lm
BIN=prog
SOURCE=palavras-reservadas.c
INPUT_PATH=input
OUTPUT_PATH=output

build:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)

debug:
	$(CC) $(SOURCE) -g $(FLAGS) -o $(BIN)

run:build
	./$(BIN) < $(INPUT_PATH)/arq01.in > $(OUTPUT_PATH)/arq01.out
	./$(BIN) < $(INPUT_PATH)/arq02.in > $(OUTPUT_PATH)/arq02.out

test:run
	-sdiff -s $(OUTPUT_PATH)/arq01.out $(OUTPUT_PATH)/arq01.res
	-sdiff -s $(OUTPUT_PATH)/arq02.out $(OUTPUT_PATH)/arq02.res

valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $(INPUT_PATH)/arq1.in > $(OUTPUT_PATH)/arq01.out
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(BIN) < $(INPUT_PATH)/arq2.in > $(OUTPUT_PATH)/arq02.out
