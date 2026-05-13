NAME = libasm.a
NASM = nasm
NASM_FLAGS = -f elf64

CC = cc
CC_FLAGS = -Wall -Wextra -Werror

SRCS = srcs/ft_strlen.s

OBJS_DIR = objs/
TESTS_SRC = tests/main.c
TEST = test

OBJS = $(SRCS:srcs/%.s=$(OBJS_DIR)%.o)

all: $(NAME)

$(OBJS_DIR)%.o: srcs/%.s
		mkdir -p $(OBJS_DIR)
		$(NASM) $(NASM_FLAGS) $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

test: $(NAME)
	$(CC) $(CC_FLAGS) $(TESTS_SRC) -L. -lasm -o $(TEST)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -r $(NAME)
	rm -r $(TEST)

re: fclean all

