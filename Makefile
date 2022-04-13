NAME = program1 program2 program3
SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INCLUDE_DIR = ./includes/
C = io.c \
	malloc_array.c \
	pooling.c
O = $(C:.c=.o)
SRCS = $(addprefix $(SRC_DIR), $(C))
OBJS = $(addprefix $(OBJ_DIR), $(O))

GCC = gcc -I$(INCLUDE_DIR)
RM = rm -rf

all : $(NAME)

program1 : $(OBJ_DIR)program1.o $(OBJS)
	$(GCC) -o program1 $^
program2 : $(OBJ_DIR)program2.o $(OBJS)
	$(GCC) -o program2 $^
program3 : $(OBJ_DIR)program3.o $(OBJS)
	$(GCC) -lpthread -o program3 $^

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(GCC) -c $< -o $@

.PHONY : re all clean test testfiles test-clean test-fclean

re : clean all

clean : 
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)program1.o
	$(RM) $(OBJ_DIR)program2.o
	$(RM) $(OBJ_DIR)program3.o
	$(RM) $(NAME)

test : all ./tests/test.sh
	sh ./tests/test.sh
testfiles : ./tests/test.c ./tests/testfiles.sh 
	$(GCC) ./tests/test.c -o ./tests/test
	sh ./tests/testfiles.sh
test-clean : 
	find ./tests/ -name "test_*" ! -name "*output" -delete
test-fclean : 
	$(RM) ./tests/test
	$(RM) ./tests/test_*