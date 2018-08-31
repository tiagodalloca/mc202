CC=gcc
FLAGS=-std=c99 -pedantic -Wall -lm
BIN=edge_detector
SOURCE=edge_detector.c
INPUT_PATH=input
OUTPUT_PATH=output

build:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)

run:build
	./$(BIN) < $(INPUT_PATH)/arq1.in > $(OUTPUT_PATH)/arq1.res
	./$(BIN) < $(INPUT_PATH)/arq2.in > $(OUTPUT_PATH)/arq2.res
	./$(BIN) < $(INPUT_PATH)/arq3.in > $(OUTPUT_PATH)/arq3.res
	./$(BIN) < $(INPUT_PATH)/arq4.in > $(OUTPUT_PATH)/arq4.res
	./$(BIN) < $(INPUT_PATH)/arq5.in > $(OUTPUT_PATH)/arq5.res

test:run
	-sdiff -s $(OUTPUT_PATH)/arq1.out $(OUTPUT_PATH)/arq1.res
	-sdiff -s $(OUTPUT_PATH)/arq2.out $(OUTPUT_PATH)/arq2.res
	-sdiff -s $(OUTPUT_PATH)/arq3.out $(OUTPUT_PATH)/arq3.res
	-sdiff -s $(OUTPUT_PATH)/arq4.out $(OUTPUT_PATH)/arq4.res
	-sdiff -s $(OUTPUT_PATH)/arq5.out $(OUTPUT_PATH)/arq5.res
