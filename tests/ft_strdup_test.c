#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libasm.h"
#include "tests.h"

#define LONG_STRING_LENGTH 1000000

/**
 * @brief Compare ft_strdup results against strdup.
 * @return Number of failed tests.
 */
int	test_ft_strdup(void)
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
	char			*strdup_res;
	char			*ft_strdup_res;
	size_t			length;
	int				content_ok;
	int				allocation_ok;
	int				failures = 0;

	memset(long_string, 'a', LONG_STRING_LENGTH);
	long_string[LONG_STRING_LENGTH] = '\0';

	tests[n - 1] = long_string;

	print_test_title("FT_STRDUP");
	for (size_t i = 0; i < n; i++)
	{
		length = strlen(tests[i]);
		strdup_res = strdup(tests[i]);
		ft_strdup_res = ft_strdup(tests[i]);
		content_ok = (strdup_res != NULL && ft_strdup_res != NULL && memcmp(strdup_res, ft_strdup_res, length + 1) == 0);
		allocation_ok = (ft_strdup_res != NULL && ft_strdup_res != tests[i]);
		printf("[%zu] Source string      : \"%.10s\"\n", i, tests[i]);
		printf("    strdup returned    : \"%.10s\"\n",
			strdup_res != NULL ? strdup_res : "(null)");
		printf("    ft_strdup returned : \"%.10s\"\n",
			ft_strdup_res != NULL ? ft_strdup_res : "(null)");
		printf("    Independent copy   : %s\n", allocation_ok ? "yes" : "no");
		printf("    Result: %s\n\n", (content_ok && allocation_ok) ? "OK" : "KO");
		if (!content_ok || !allocation_ok)
			failures++;
		free(strdup_res);
		if (allocation_ok)
			free(ft_strdup_res);
	}

	free(long_string);
	return (failures);
}
