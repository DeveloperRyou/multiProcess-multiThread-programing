NAME = program1 program2 program3

.PHONY : all clean test

all : $(NAME)

clean : 
	rm -rf 

test : ./tests/test.c
	gcc ./tests/test.c