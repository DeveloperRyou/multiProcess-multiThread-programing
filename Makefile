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

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(GCC) -c $< -o $@

program1 : $(OBJ_DIR)program1.o $(OBJS)
	$(GCC) -o program1 $^
program2 : $(OBJ_DIR)program2.o $(OBJS)
	$(GCC) -o program2 $^
program3 : $(OBJ_DIR)program3.o $(OBJS)
	$(GCC) -o program3 $^

.PHONY : all clean test test-clean

all : $(NAME)

clean : 
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)program1.o
	$(RM) $(OBJ_DIR)program2.o
	$(RM) $(OBJ_DIR)program3.o
	$(RM) $(NAME)

test : ./tests/test.c
	$(GCC) ./tests/test.c -o test
	
test-clean : 
	$(RM) test