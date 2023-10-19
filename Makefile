all:
	@gcc -o trab1 main.c src/data_structures/*.c src/Input_Output/*.c -lm
	@echo 'Compilado!'