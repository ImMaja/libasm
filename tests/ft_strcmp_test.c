#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libasm.h"
#include "tests.h"

#define LONG_STRING_LENGTH 1000000

typedef struct s_strcmp_test
{
	const char	*description;
	const char	*s1;
	const char	*s2;
}	t_strcmp_test;

static int	have_same_sign(const int first, const int second)
{
	return ( (first == 0 && second == 0)
		|| (first < 0 && second < 0)
		|| (first > 0 && second > 0) );
}


/**
 * @brief Compare ft_strcmp results against strcmp.
 * @return Number of failed tests.
 */
int	test_ft_strcmp(void)
{
	t_strcmp_test	tests[] = {
		{"equal empty strings", "", ""},
		{"equal strings", "abc", "abc"},
		{"different characters", "abc", "abe"},
		{"different characters, reversed", "abe", "abc"},
		{"shorter first string", "abc", "abcd"},
		{"longer first string", "abcd", "abc"},
		{"empty first string", "", "a"},
		{"empty second string", "a", ""},
		{"line break", "Hello World!", "Hello World\n!"},
		{"unsigned bytes: 0xff > 0x01", "\xff", "\x01"},
		{"long equal strings", NULL, NULL},
		{"difference at end of long strings", NULL, NULL}
	};

	size_t			i = 0;
	const size_t	n = sizeof(tests) / sizeof(tests[0]);
	char			*long_s1 = xmalloc(LONG_STRING_LENGTH + 1);
	char			*long_s2 = xmalloc(LONG_STRING_LENGTH + 1);
	char			*long_s3 = xmalloc(LONG_STRING_LENGTH + 1);
	int				strcmp_res;
	int				ft_strcmp_res;
	int				result_ok;
	int				failures = 0;

	memset(long_s1, 'a', LONG_STRING_LENGTH);
	memset(long_s2, 'a', LONG_STRING_LENGTH);
	memset(long_s3, 'a', LONG_STRING_LENGTH);

	long_s1[LONG_STRING_LENGTH] = '\0';
	long_s2[LONG_STRING_LENGTH] = '\0';
	long_s3[LONG_STRING_LENGTH] = '\0';
	long_s3[LONG_STRING_LENGTH - 1] = 'b';

	tests[n - 2].s1 = long_s1;
	tests[n - 2].s2 = long_s2;
	tests[n - 1].s1 = long_s1;
	tests[n - 1].s2 = long_s3;

	print_test_title("FT_STRCMP");
	for (i = 0; i < n; i++) {
		strcmp_res = strcmp(tests[i].s1, tests[i].s2);
		ft_strcmp_res = ft_strcmp(tests[i].s1, tests[i].s2);
		result_ok = have_same_sign(strcmp_res, ft_strcmp_res);
		printf("[%zu] %s\n", i, tests[i].description);
		printf("    s1: \"%.10s\"\n", tests[i].s1);
		printf("    s2: \"%.10s\"\n", tests[i].s2);
		printf("    strcmp returned    : %d\n", strcmp_res);
		printf("    ft_strcmp returned : %d\n", ft_strcmp_res);
		printf("    Result: %s\n\n", result_ok ? "OK" : "KO");
		if (!result_ok)
			failures++;
	}

	free(long_s1);
	free(long_s2);
	free(long_s3);

	/** Special case, strcmp call optimized by compiler at compile time */
	printf("[%zu] %s\n", i + 1, "GCC strcmp");
	printf("    s1: \"%.10s\"\n", "abc");
	printf("    s2: \"%.10s\"\n", "abe");

	strcmp_res = strcmp("abc", "abe");
	ft_strcmp_res = ft_strcmp("abc", "abe");
	result_ok = have_same_sign(strcmp_res, ft_strcmp_res);

	printf("    gcc strcmp returned : %d\n", strcmp_res);
	printf("    ft_strcmp returned  : %d\n", ft_strcmp_res);
	printf("    Result: %s\n\n", result_ok ? "OK" : "KO");
	if (!result_ok)
		failures++;
	return (failures);
}
