#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libasm.h"
#include "tests.h"

#define LONG_STRING_LENGTH 1000000

/**
 * @brief Compare ft_strlen results against strlen.
 * @return Number of failed tests.
 */
int	test_ft_strlen(void)
{
	const char	*tests[] = {
		"",
		"a",
		"Hello World!",
		"Hello World\n!",
		"Spaces     between     words",
		"01234567890123456789012345678901234567890123456789",
		NULL // will be long_string later
	};

	const size_t	n = sizeof(tests) / sizeof(tests[0]);
	char			*long_string = xmalloc(LONG_STRING_LENGTH + 1);
	size_t			strlen_res;
	size_t			ft_strlen_res;
	int				failures = 0;

	memset(long_string, 'a', LONG_STRING_LENGTH);
	long_string[LONG_STRING_LENGTH] = '\0';

	tests[n - 1] = long_string;

	print_test_title("FT_STRLEN");
	for (size_t i = 0; i < n; i++) {
		strlen_res = strlen(tests[i]);
		ft_strlen_res = ft_strlen(tests[i]);
		printf("[%zu] Original string    : \"%.10s\"\n", i, tests[i]);
		printf("    strlen returned    : %zu\n", strlen_res);
		printf("    ft_strlen returned : %zu\n", ft_strlen_res);
		printf("    Result: %s\n\n", (strlen_res == ft_strlen_res) ? "OK" : "KO");
		if (strlen_res != ft_strlen_res)
			failures++;
	}

	free(long_string);
	return (failures);
}
