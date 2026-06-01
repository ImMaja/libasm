#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libasm.h"
#include "tests.h"

#define LONG_STRING_LENGTH 1000000

/**
 * @brief Compare ft_strcpy results against strcpy.
 * @return Number of failed tests.
 */
int	test_ft_strcpy(void)
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
	char			*strcpy_dest;
	char			*ft_strcpy_dest;
	char			*ft_strcpy_ret;
	size_t			length;
	int				content_ok;
	int				return_ok;
	int				failures = 0;

	memset(long_string, 'a', LONG_STRING_LENGTH);
	long_string[LONG_STRING_LENGTH] = '\0';

	tests[n - 1] = long_string;

	print_test_title("FT_STRCPY");
	for (size_t i = 0; i < n; i++)
	{
		length = strlen(tests[i]);
		strcpy_dest = xmalloc(length + 1);
		ft_strcpy_dest = xmalloc(length + 1);
		strcpy(strcpy_dest, tests[i]);
		ft_strcpy_ret = ft_strcpy(ft_strcpy_dest, tests[i]);
		content_ok = memcmp(strcpy_dest, ft_strcpy_dest, length + 1) == 0;
		return_ok = ft_strcpy_ret == ft_strcpy_dest;
		printf("[%zu] Source string          : \"%.10s\"\n", i, tests[i]);
		printf("    strcpy destination     : \"%.10s\"\n", strcpy_dest);
		printf("    ft_strcpy destination  : \"%.10s\"\n", ft_strcpy_dest);
		printf("    Result: %s\n\n", (content_ok && return_ok) ? "OK" : "KO");
		if (!content_ok || !return_ok)
			failures++;
		free(strcpy_dest);
		free(ft_strcpy_dest);
	}

	free(long_string);
	return (failures);
}
