#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>


size_t	ft_strlen(const char *s);


/**
 * @brief Create the string set used by the tests.
 * @param n Number of strings to allocate and check.
 * @return A null-terminated array of allocated strings.
 */
char	**create_test_strings(const uint8_t n) {
	char	**tests;

	tests = (char **) malloc(sizeof(char *) * (n + 1));
	if (!tests) {
		write(2, "Heap allocation failed. Aborted\n", 32);
		exit(1);
	}

	tests[0] = strdup("");
	tests[1] = strdup("a");
	tests[2] = strdup("Hello World!");
	tests[3] = strdup("Hello \0World!");
	tests[4] = strdup("Hello World\n!");
	tests[5] = (char *) malloc(sizeof(char) * 256);
	tests[6] = (char *) malloc(sizeof(char) * 42069);
	tests[7] = NULL;

	for (uint8_t i = 0 ; i < n; i++) {
		if (*(tests + i) == NULL) {
			write(2, "Heap allocation failed. Aborted\n", 32);
			exit(1);
		}
	}

	for (uint8_t i = 0; i < 255; i++)
		*(*(tests + 5) + i) = i;
	*(*(tests + 5) + 255) = '\0';

	memset(*(tests + 6), 42, 42068);
	*(*(tests + 6) + 42068) = '\0';

	return (tests);
}


/**
 * @brief Compare ft_strlen results against strlen.
 * @param tests Array of strings to test.
 * @param n Number of strings in the array.
 */
void	test_ft_strlen(char **tests, const uint8_t n) {
	size_t	strlen_res;
	size_t	ft_strlen_res;

	for (uint8_t i = 0 ; i < n ; i++) {
		strlen_res = strlen(*(tests + i));
		ft_strlen_res = ft_strlen(*(tests + i));

		printf("[%d] Original string: %.20s\nstrlen_res:    %zu\nft_strlen_res: %zu\n\n", i, *(tests + i), strlen_res, ft_strlen_res);
	}
}


/**
 * @brief Run all libdsm tests.
 * @return 0 on success.
 */
int	main(void) {
	const uint8_t	n = 7; // Number of strings for tests
	char			**tests = create_test_strings(n); // Array of test strings

	printf("    ---- FT_STRLEN ----\n\n");
	test_ft_strlen(tests, n);

	// Free test strings and test array
	for (uint8_t i = 0 ; i < n ; i++)
		free(*(tests + i));
	free(tests);

	return (0);
}
