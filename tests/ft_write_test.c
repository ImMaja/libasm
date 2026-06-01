#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/libasm.h"
#include "tests.h"

#define LONG_STRING_LENGTH 42069
#define OUTPUT_FILE "tests/ft_write_output.txt"

typedef struct s_write_test
{
	const char	*description;
	const char	*buffer;
	size_t		count;
}	t_write_test;

/**
 * @brief Compare write and ft_write return values on stdout.
 */
static int	test_stdout(const t_write_test *tests, const size_t n)
{
	ssize_t	write_res;
	ssize_t	ft_write_res;
	int		failures = 0;

	printf("    ---- FT_WRITE STDOUT ----\n\n");
	for (size_t i = 0; i < n; i++) {
		printf("[%zu] %s\n", i, tests[i].description);
		printf("    write output    : \"");
		fflush(stdout);
		write_res = write(STDOUT_FILENO, tests[i].buffer, tests[i].count);
		printf("\"\n");
		printf("    ft_write output : \"");
		fflush(stdout);
		ft_write_res = ft_write(STDOUT_FILENO, tests[i].buffer, tests[i].count);
		printf("\"\n");
		printf("    write returned    : %zd\n", write_res);
		printf("    ft_write returned : %zd\n", ft_write_res);
		printf("    Result: %s\n\n", (write_res == ft_write_res) ? "OK" : "KO");
		if (write_res != ft_write_res)
			failures++;
	}
	return (failures);
}

/**
 * @brief Write test buffers and a long string to a file with ft_write.
 */
static int	test_file(const t_write_test *tests, const size_t n,
	const char *long_string)
{
	int		fd;
	ssize_t	ft_write_res;
	int		failures = 0;

	fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror("Could not open ft_write output file");
		exit(EXIT_FAILURE);
	}
	printf("    ---- FT_WRITE FILE ----\n\n");
	for (size_t i = 0; i < n; i++) {
		ft_write_res = ft_write(fd, tests[i].buffer, tests[i].count);
		printf("[%zu] %s: %zd byte(s) written\n", i, tests[i].description, ft_write_res);
		if (ft_write_res != (ssize_t)tests[i].count)
			failures++;
	}
	ft_write_res = ft_write(fd, long_string, LONG_STRING_LENGTH);
	printf("[%zu] long string: %zd byte(s) written\n\n", n, ft_write_res);
	if (ft_write_res != LONG_STRING_LENGTH)
		failures++;
	if (close(fd) == -1) {
		perror("Could not close ft_write output file");
		exit(EXIT_FAILURE);
	}
	printf("    Output written to %s\n\n", OUTPUT_FILE);
	return (failures);
}

/**
 * @brief Compare write and ft_write errors for an invalid file descriptor.
 */
static int	test_error(void)
{
	const char	*buffer = "Hello World!";
	ssize_t		write_res;
	ssize_t		ft_write_res;
	int			write_errno;
	int			ft_write_errno;
	int			result_ok;

	errno = 0;
	write_res = write(-1, buffer, 12);
	write_errno = errno;
	errno = 0;
	ft_write_res = ft_write(-1, buffer, 12);
	ft_write_errno = errno;
	result_ok = (write_res == ft_write_res && write_errno == ft_write_errno);
	printf("    ---- FT_WRITE ERROR ----\n\n");
	printf("    write returned    : %zd | errno: %d\n", write_res, write_errno);
	printf("    ft_write returned : %zd | errno: %d\n", ft_write_res, ft_write_errno);
	printf("    Result: %s\n\n", result_ok ? "OK" : "KO");
	return (!result_ok);
}

/**
 * @brief Compare ft_write results against write.
 * @return Number of failed tests.
 */
int	test_ft_write(void)
{
	static const char	embedded_null[] = {'a', 'b', 'c', '\0', 'd', 'e', 'f'};
	const t_write_test	tests[] = {
		{"zero bytes", "", 0},
		{"single character", "a", 1},
		{"simple string", "Hello World!", 12},
		{"line break", "Hello\nWorld!", 12},
		{"partial buffer", "abcdefghij", 4},
		{"embedded null byte", embedded_null, sizeof(embedded_null)}
	};
	const size_t		n = sizeof(tests) / sizeof(tests[0]);
	char			*long_string = xmalloc(LONG_STRING_LENGTH);
	int				failures;

	memset(long_string, 'a', LONG_STRING_LENGTH);
	failures = test_stdout(tests, n);
	failures += test_file(tests, n, long_string);
	failures += test_error();
	free(long_string);
	return (failures);
}
