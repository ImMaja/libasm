#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>


size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);

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

		printf("[%d] Original string    : \"%.10s\"\n", i, *(tests + i));
		printf("    strlen returned    : %zu\n", strlen_res);
		printf("    ft_strlen returned : %zu\n", ft_strlen_res);
		printf("    Result: %s\n\n", (strlen_res == ft_strlen_res) ? "OK" : "KO");
	}
}


/**
 * @brief Compare ft_strcpy results against strcpy.
 * @param tests Array of strings to test.
 * @param n Number of strings in the array.
 */
void	test_ft_strcpy(char **tests, const uint8_t n) {
	char		*src = NULL;
	char		*strcpy_dest = NULL;
	char		*ft_strcpy_dest = NULL;
	char		*ft_strcpy_ret = NULL;
	size_t		length = 0;

	for (uint8_t i = 0 ; i < n ; i++) {
		src = *(tests + i);
		length = strlen(src);

		// Allocate enought memory for both destinations
		strcpy_dest = (char *) malloc(sizeof(char) * (length + 1) );
		ft_strcpy_dest = (char *) malloc(sizeof(char) * (length + 1) );
		if (!strcpy_dest || !ft_strcpy_dest) {
			write(2, "Heap allocation failed. Aborted\n", 32);
			exit(1);
		}

		// printf("[%d] \n", i);
		printf("[%d] src content  : \"%.10s\"\n", i, src);

		// Do the coppiiiieess
		strcpy(strcpy_dest, *(tests + i));
		ft_strcpy_ret = ft_strcpy(ft_strcpy_dest, *(tests + i));

		printf("    dest content : \"%.10s\"\n", ft_strcpy_dest);
		printf("    Same content as original strcpy ? : %s\n", (memcmp(strcpy_dest, ft_strcpy_dest, length + 1) == 0) ? "YES" : "NO");
		printf("    ft_strcpy_dest addr : %p | ft_strcpy_ret addr : %p | Same addr ? : %s\n\n", ft_strcpy_dest, ft_strcpy_ret, (ft_strcpy_dest == ft_strcpy_ret) ? "YES" : "NO");

		free(strcpy_dest);
		free(ft_strcpy_dest);
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

	printf("    ---- FT_STRCPY ----\n\n");
	test_ft_strcpy(tests, n);

	// Free test strings and test array
	for (uint8_t i = 0 ; i < n ; i++)
		free(*(tests + i));
	free(tests);

	return (0);
}
