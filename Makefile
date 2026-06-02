NAME = libasm.a
NASM = nasm
NASM_FLAGS = -f elf64

CC = cc
CC_FLAGS = -Wall -Wextra -Werror

SRC = src/ft_strlen.s \
	src/ft_strcpy.s \
	src/ft_strcmp.s \
	src/ft_write.s \
	src/ft_read.s \
	src/ft_strdup.s

SRC_BONUS = bonus/src/ft_atoi_base_bonus.s


TESTS_SRC = tests/ft_strlen_test.c \
	tests/ft_strcpy_test.c \
	tests/ft_strcmp_test.c \
	tests/ft_write_test.c \
	tests/ft_read_test.c \
	tests/ft_strdup_test.c \
	tests/helper.c \
	tests/main.c

TESTS_SRC_BONUS = bonus/tests/ft_atoi_base_test_bonus.c \
	bonus/tests/main_bonus.c


OBJS_DIR = objs/
OBJS_BONUS_DIR = $(OBJS_DIR)bonus/
BONUS_STAMP = $(OBJS_BONUS_DIR).built
TEST = test

OBJS = $(SRC:src/%.s=$(OBJS_DIR)%.o)
OBJS_BONUS = $(SRC_BONUS:bonus/src/%.s=$(OBJS_BONUS_DIR)%.o)

.PHONY: all bonus test clean fclean re

all: $(NAME)

$(OBJS_DIR)%.o: src/%.s
		mkdir -p $(OBJS_DIR)
		$(NASM) $(NASM_FLAGS) $< -o $@

$(OBJS_BONUS_DIR)%.o: bonus/src/%.s
		mkdir -p $(OBJS_BONUS_DIR)
		$(NASM) $(NASM_FLAGS) $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(BONUS_STAMP)

$(BONUS_STAMP): $(NAME) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)
	touch $(BONUS_STAMP)

test: $(NAME) $(TESTS_SRC)
	$(CC) $(CC_FLAGS) $(TESTS_SRC) -L. -lasm -o $(TEST)
	./$(TEST)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST)

re: fclean all
