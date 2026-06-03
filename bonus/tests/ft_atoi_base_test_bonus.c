#include <stdio.h>

#include "../include/libasm_bonus.h"
#include "tests_bonus.h"

typedef struct s_atoi_base_test
{
	const char	*description;
	char		*str;
	char		*base;
	int			expected;
}	t_atoi_base_test;

static const char	*safe_str(const char *str)
{
	if (str == NULL)
		return ("(null)");
	return (str);
}

/**
 * @brief Test ft_atoi_base against expected conversion results.
 * @return Number of failed tests.
 */
int	test_ft_atoi_base(void)
{
	t_atoi_base_test	tests[] = {
		{ "empty string", "", "0123456789", 0 },
		{ "positive decimal", "42", "0123456789", 42 },
		{ "negative decimal", "-42", "0123456789", -42 },
		{ "leading whitespaces", " \t\n\v\f\r42", "0123456789", 42 },
		{ "multiple signs", "---+--+1234ab567", "0123456789", -1234 },
		{ "binary base", "101010", "01", 42 },
		{ "lowercase hexadecimal", "2a", "0123456789abcdef", 42 },
		{ "custom base", "oney", "poneyvif", 668 },
		{ "stop at invalid char", "10z10", "01", 2 },
		{ "only signs", "--+-", "0123456789", 0 },
		{ "null string", NULL, "0123456789", 0 },
		{ "null base", "42", NULL, 0 },
		{ "empty base", "42", "", 0 },
		{ "base length one", "42", "0", 0 },
		{ "base with duplicate", "42", "01234567890", 0 },
		{ "base with plus sign", "42", "0123456789+", 0 },
		{ "base with minus sign", "42", "0123456789-", 0 },
		{ "base with whitespace", "42", "01234 56789", 0 }
	};

	const size_t	n = sizeof(tests) / sizeof(tests[0]);
	int				ft_atoi_base_res;
	int				failures = 0;

	print_test_title("FT_ATOI_BASE");
	for (size_t i = 0; i < n; i++)
	{
		ft_atoi_base_res = ft_atoi_base(tests[i].str, tests[i].base);
		printf("[%zu] %s\n", i, tests[i].description);
		printf("    str              : \"%.20s\"\n", safe_str(tests[i].str));
		printf("    base             : \"%.20s\"\n", safe_str(tests[i].base));
		printf("    expected         : %d\n", tests[i].expected);
		printf("    ft_atoi_base ret : %d\n", ft_atoi_base_res);
		printf("    Result: %s\n\n", (ft_atoi_base_res == tests[i].expected) ? "OK" : "KO");
		if (ft_atoi_base_res != tests[i].expected)
			failures++;
	}
	return (failures);
}
