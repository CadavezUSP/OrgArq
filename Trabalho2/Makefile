SRC = ./sources
INC = ./includes
EXE = trabalho2
FLAGS = -Wall -Werror -I

all: compile

compile:
	@gcc -o $(EXE) $(SRC)/*.c $(FLAGS) $(INC)

run:
	@./$(EXE)

zip:
	@zip -r Trabalho2 $(SRC) $(INC) Makefile