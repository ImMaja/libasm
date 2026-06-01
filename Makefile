NAME = libasm.a
NASM = nasm
NASM_FLAGS = -f elf64

CC = cc
CC_FLAGS = -Wall -Wextra -Werror -g3

SRCS = srcs/ft_strlen.s \
	srcs/ft_strcpy.s \
	srcs/ft_strcmp.s \
	srcs/ft_write.s

TESTS_SRC = tests/ft_strlen_test.c \
	tests/ft_strcpy_test.c \
	tests/ft_strcmp_test.c \
	tests/ft_write_test.c \
	tests/helper.c \
	tests/main.c

OBJS_DIR = objs/
TEST = test

OBJS = $(SRCS:srcs/%.s=$(OBJS_DIR)%.o)

.PHONY: all test clean fclean re

all: $(NAME)

$(OBJS_DIR)%.o: srcs/%.s
		mkdir -p $(OBJS_DIR)
		$(NASM) $(NASM_FLAGS) $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

test: $(NAME) $(TESTS_SRC)
	$(CC) $(CC_FLAGS) $(TESTS_SRC) -L. -lasm -o $(TEST)
	./$(TEST)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST)

re: fclean all
