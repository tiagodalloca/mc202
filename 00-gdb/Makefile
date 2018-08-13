CC=gcc
FLAGS=-Wall
OUTPUT=intermediario
SOURCE=intermediario.c
INPUT_PATH=input
OUTPUT_PATH=output

all: build

build:
	$(CC) $(FLAGS) $(SOURCE) -o $(OUTPUT)

run:build
	./$(OUTPUT) < $(INPUT_PATH)/arq1.in > $(OUTPUT_PATH)/arq1.res
	./$(OUTPUT) < $(INPUT_PATH)/arq2.in > $(OUTPUT_PATH)/arq2.res
	./$(OUTPUT) < $(INPUT_PATH)/arq3.in > $(OUTPUT_PATH)/arq3.res
	./$(OUTPUT) < $(INPUT_PATH)/arq4.in > $(OUTPUT_PATH)/arq4.res

test:run
	-sdiff -s $(OUTPUT_PATH)/arq1.out $(OUTPUT_PATH)/arq1.res
	-sdiff -s $(OUTPUT_PATH)/arq2.out $(OUTPUT_PATH)/arq2.res
	-sdiff -s $(OUTPUT_PATH)/arq3.out $(OUTPUT_PATH)/arq3.res
	-sdiff -s $(OUTPUT_PATH)/arq4.out $(OUTPUT_PATH)/arq4.res
