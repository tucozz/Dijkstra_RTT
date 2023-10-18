all:
	@gcc -o trab1 src/*.c src/data_structures/*.c src/Input_Output/*.c -lm
	@echo 'Compilado!'