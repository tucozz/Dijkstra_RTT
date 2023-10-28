all:
	@gcc -g -o trab1 main.c src/data_structures/*.c src/algorithms/*.c src/Input_Output/*.c -lm
	@echo 'Compilado!'