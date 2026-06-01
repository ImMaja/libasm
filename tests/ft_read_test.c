#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/libasm.h"
#include "tests.h"

#define INPUT_FILE "tests/ft_read_input.txt"
#define BUFFER_SIZE 128

typedef struct s_read_test
{
	const char	*description;
	size_t		count;
}	t_read_test;

static int	open_input_file(void)
{
	int	fd;

	fd = open(INPUT_FILE, O_RDONLY);
	if (fd == -1) {
		perror("Could not open ft_read input file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * @brief Compare read and ft_read results on a text file.
 */
static int	test_file(const t_read_test *tests, const size_t n)
{
	char	read_buffer[BUFFER_SIZE + 1];
	char	ft_read_buffer[BUFFER_SIZE + 1];
	ssize_t	read_res;
	ssize_t	ft_read_res;
	int		read_fd;
	int		ft_read_fd;
	int		result_ok;
	int		failures = 0;

	print_test_title("FT_READ FILE");
	for (size_t i = 0; i < n; i++) {
		read_fd = open_input_file();
		ft_read_fd = open_input_file();
		memset(read_buffer, 0, sizeof(read_buffer));
		memset(ft_read_buffer, 0, sizeof(ft_read_buffer));
		read_res = read(read_fd, read_buffer, tests[i].count);
		ft_read_res = ft_read(ft_read_fd, ft_read_buffer, tests[i].count);
		result_ok = (read_res == ft_read_res
				&& (read_res <= 0
					|| memcmp(read_buffer, ft_read_buffer, read_res) == 0));
		printf("[%zu] %s\n", i, tests[i].description);
		printf("    read buffer    : \"%.50s\"\n", read_buffer);
		printf("    ft_read buffer : \"%.50s\"\n", ft_read_buffer);
		printf("    read returned    : %zd\n", read_res);
		printf("    ft_read returned : %zd\n", ft_read_res);
		printf("    Result: %s\n\n", result_ok ? "OK" : "KO");
		if (!result_ok)
			failures++;
		if (close(read_fd) == -1 || close(ft_read_fd) == -1) {
			perror("Could not close ft_read input file");
			exit(EXIT_FAILURE);
		}
	}
	return (failures);
}

/**
 * @brief Check that ft_read returns zero after reaching end of file.
 */
static int	test_eof(void)
{
	char	read_buffer[BUFFER_SIZE];
	char	ft_read_buffer[BUFFER_SIZE];
	ssize_t	read_res;
	ssize_t	ft_read_res;
	int		read_fd;
	int		ft_read_fd;
	int		result_ok;

	read_fd = open_input_file();
	ft_read_fd = open_input_file();
	read(read_fd, read_buffer, BUFFER_SIZE);
	ft_read(ft_read_fd, ft_read_buffer, BUFFER_SIZE);
	read_res = read(read_fd, read_buffer, BUFFER_SIZE);
	ft_read_res = ft_read(ft_read_fd, ft_read_buffer, BUFFER_SIZE);
	result_ok = (read_res == 0 && ft_read_res == read_res);
	print_test_title("FT_READ EOF");
	printf("    read returned after EOF    : %zd\n", read_res);
	printf("    ft_read returned after EOF : %zd\n", ft_read_res);
	printf("    Result: %s\n\n", result_ok ? "OK" : "KO");
	if (close(read_fd) == -1 || close(ft_read_fd) == -1) {
		perror("Could not close ft_read input file");
		exit(EXIT_FAILURE);
	}
	return (!result_ok);
}

/**
 * @brief Compare read and ft_read errors for an invalid file descriptor.
 */
static int	test_error(void)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	read_res;
	ssize_t	ft_read_res;
	int		read_errno;
	int		ft_read_errno;
	int		result_ok;

	errno = 0;
	read_res = read(-1, buffer, BUFFER_SIZE);
	read_errno = errno;
	errno = 0;
	ft_read_res = ft_read(-1, buffer, BUFFER_SIZE);
	ft_read_errno = errno;
	result_ok = (read_res == ft_read_res && read_errno == ft_read_errno);
	print_test_title("FT_READ ERROR");
	printf("    read returned    : %zd | errno: %d\n", read_res, read_errno);
	printf("    ft_read returned : %zd | errno: %d\n", ft_read_res,
		ft_read_errno);
	printf("    Result: %s\n\n", result_ok ? "OK" : "KO");
	return (!result_ok);
}

/**
 * @brief Compare ft_read results against read.
 * @return Number of failed tests.
 */
int	test_ft_read(void)
{
	const t_read_test	tests[] = {
		{"zero bytes", 0},
		{"first five bytes", 5},
		{"whole text file", BUFFER_SIZE}
	};
	const size_t	n = sizeof(tests) / sizeof(tests[0]);
	int				failures = 0;

	failures = test_file(tests, n);
	failures += test_eof();
	failures += test_error();
	return (failures);
}
