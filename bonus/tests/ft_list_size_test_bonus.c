#include <stdio.h>

#include "../include/libasm_bonus.h"
#include "tests_bonus.h"

typedef struct s_list_size_test
{
	const char	*description;
	t_list		*list;
	int			expected;
}	t_list_size_test;

static const char	*test_status(int ok)
{
	if (ok)
		return ("OK");
	return ("KO");
}

/**
 * @brief Test ft_list_size against expected linked-list sizes.
 * @return Number of failed tests.
 */
int	test_ft_list_size(void)
{
	t_list	one = { "one", NULL };
	t_list	two_tail = { "two_tail", NULL };
	t_list	two_head = { "two_head", &two_tail };
	t_list	null_data_tail = { NULL, NULL };
	t_list	null_data_head = { NULL, &null_data_tail };
	t_list	long_list[5] = {
		{ "0", &long_list[1] },
		{ "1", &long_list[2] },
		{ "2", &long_list[3] },
		{ "3", &long_list[4] },
		{ "4", NULL }
	};
	t_list_size_test	tests[] = {
		{ "empty list", NULL, 0 },
		{ "one node", &one, 1 },
		{ "two nodes", &two_head, 2 },
		{ "two nodes with NULL data", &null_data_head, 2 },
		{ "five nodes", long_list, 5 }
	};

	const size_t	n = sizeof(tests) / sizeof(tests[0]);
	int				ft_list_size_res;
	int				failures = 0;

	print_test_title("FT_LIST_SIZE");
	for (size_t i = 0; i < n; i++)
	{
		ft_list_size_res = ft_list_size(tests[i].list);
		printf("[%zu] %s\n", i, tests[i].description);
		printf("    list             : %p\n", (void *)tests[i].list);
		printf("    expected         : %d\n", tests[i].expected);
		printf("    ft_list_size ret : %d\n", ft_list_size_res);
		printf("    Result: %s\n\n",
			test_status(ft_list_size_res == tests[i].expected));
		if (ft_list_size_res != tests[i].expected)
			failures++;
	}
	return (failures);
}
