#include <stdio.h>

#include "../include/libasm_bonus.h"
#include "tests_bonus.h"

#define SORT_CASE_MAX 10

typedef struct s_list_sort_test
{
	const char	*description;
	size_t		count;
	int			values[SORT_CASE_MAX];
	int			expected[SORT_CASE_MAX];
}	t_list_sort_test;

typedef struct s_list_sort_str_test
{
	const char	*description;
	size_t		count;
	char		*values[SORT_CASE_MAX];
	char		*expected[SORT_CASE_MAX];
}	t_list_sort_str_test;

static const char	*test_status(int ok)
{
	if (ok)
		return ("OK");
	return ("KO");
}

static int	str_cmp_value(const char *left, const char *right)
{
	size_t	i = 0;

	while (left[i] != '\0' && left[i] == right[i])
		i++;
	return ((unsigned char)left[i] - (unsigned char)right[i]);
}

#if defined(__GNUC__) || defined(__clang__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wold-style-definition"
#endif
static int	cmp_int(left, right)
void	*left;
void	*right;
{
	const int	left_value = *(int *)left;
	const int	right_value = *(int *)right;

	if (left_value < right_value)
		return (-1);
	if (left_value > right_value)
		return (1);
	return (0);
}

static int	cmp_str(left, right)
void	*left;
void	*right;
{
	return (str_cmp_value(left, right));
}
#if defined(__GNUC__) || defined(__clang__)
# pragma GCC diagnostic pop
#endif

static void	print_bool_check(const char *label, int ok)
{
	printf("    %-17s: %s\n", label, test_status(ok));
}

static void	print_int_array(const int *values, size_t count)
{
	printf("[");
	for (size_t i = 0; i < count; i++)
	{
		if (i > 0)
			printf(", ");
		printf("%d", values[i]);
	}
	printf("]");
}

static void	print_str_array(char *const *values, size_t count)
{
	printf("[");
	for (size_t i = 0; i < count; i++)
	{
		if (i > 0)
			printf(", ");
		printf("\"%s\"", values[i]);
	}
	printf("]");
}

static int	find_node_index(t_list *node, t_list *nodes, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (node == &nodes[i])
			return ((int)i);
	}
	return (-1);
}

static void	print_list_values(t_list *list, t_list *nodes, size_t count)
{
	size_t	i = 0;
	int		node_index;

	printf("[");
	while (list != NULL && i < count + 1)
	{
		if (i > 0)
			printf(", ");
		node_index = find_node_index(list, nodes, count);
		if (node_index < 0)
		{
			printf("?");
			printf("]");
			return ;
		}
		printf("%d", *(int *)nodes[node_index].data);
		list = list->next;
		i++;
	}
	if (list != NULL)
	{
		if (i > 0)
			printf(", ");
		printf("...");
	}
	printf("]");
}

static void	print_str_list_values(t_list *list, t_list *nodes, size_t count)
{
	size_t	i = 0;
	int		node_index;

	printf("[");
	while (list != NULL && i < count + 1)
	{
		if (i > 0)
			printf(", ");
		node_index = find_node_index(list, nodes, count);
		if (node_index < 0)
		{
			printf("?");
			printf("]");
			return ;
		}
		printf("\"%s\"", (char *)nodes[node_index].data);
		list = list->next;
		i++;
	}
	if (list != NULL)
	{
		if (i > 0)
			printf(", ");
		printf("...");
	}
	printf("]");
}

static int	list_has_all_nodes_once(t_list *list, t_list *nodes, size_t count)
{
	int		seen[SORT_CASE_MAX] = { 0 };
	int		node_index;
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (list == NULL)
			return (0);
		node_index = find_node_index(list, nodes, count);
		if (node_index < 0 || seen[node_index])
			return (0);
		seen[node_index] = 1;
		list = list->next;
		i++;
	}
	return (list == NULL);
}

static int	list_matches_values(t_list *list, const int *expected, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (list == NULL || *(int *)list->data != expected[i])
			return (0);
		list = list->next;
	}
	return (list == NULL);
}

static int	list_matches_strings(t_list *list, char *const *expected, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (list == NULL || str_cmp_value(list->data, expected[i]) != 0)
			return (0);
		list = list->next;
	}
	return (list == NULL);
}

static void	init_nodes(t_list *nodes, int *values, const t_list_sort_test *test)
{
	for (size_t i = 0; i < test->count; i++)
	{
		values[i] = test->values[i];
		nodes[i].data = &values[i];
		if (i + 1 < test->count)
			nodes[i].next = &nodes[i + 1];
		else
			nodes[i].next = NULL;
	}
}

static void	init_str_nodes(t_list *nodes, const t_list_sort_str_test *test)
{
	for (size_t i = 0; i < test->count; i++)
	{
		nodes[i].data = test->values[i];
		if (i + 1 < test->count)
			nodes[i].next = &nodes[i + 1];
		else
			nodes[i].next = NULL;
	}
}

static int	run_sort_case(size_t index, const t_list_sort_test *test)
{
	t_list	nodes[SORT_CASE_MAX];
	int		values[SORT_CASE_MAX];
	t_list	*list;
	int		values_ok;
	int		nodes_ok;
	int		ok;

	init_nodes(nodes, values, test);
	if (test->count == 0)
		list = NULL;
	else
		list = &nodes[0];
	ft_list_sort(&list, cmp_int);
	values_ok = list_matches_values(list, test->expected, test->count);
	nodes_ok = list_has_all_nodes_once(list, nodes, test->count);
	ok = values_ok && nodes_ok;
	printf("[%zu] %s\n", index, test->description);
	printf("    before sort      : ");
	print_int_array(test->values, test->count);
	printf("\n");
	printf("    expected         : ");
	print_int_array(test->expected, test->count);
	printf("\n");
	printf("    actual           : ");
	print_list_values(list, nodes, test->count);
	printf("\n");
	print_bool_check("sorted values", values_ok);
	print_bool_check("same nodes", nodes_ok);
	printf("    Result: %s\n\n", test_status(ok));
	return (!ok);
}

static int	run_string_sort_case(size_t index, const t_list_sort_str_test *test)
{
	t_list	nodes[SORT_CASE_MAX];
	t_list	*list;
	int		values_ok;
	int		nodes_ok;
	int		ok;

	init_str_nodes(nodes, test);
	list = &nodes[0];
	ft_list_sort(&list, cmp_str);
	values_ok = list_matches_strings(list, test->expected, test->count);
	nodes_ok = list_has_all_nodes_once(list, nodes, test->count);
	ok = values_ok && nodes_ok;
	printf("[%zu] %s\n", index, test->description);
	printf("    before sort      : ");
	print_str_array(test->values, test->count);
	printf("\n");
	printf("    expected         : ");
	print_str_array(test->expected, test->count);
	printf("\n");
	printf("    actual           : ");
	print_str_list_values(list, nodes, test->count);
	printf("\n");
	print_bool_check("sorted values", values_ok);
	print_bool_check("same nodes", nodes_ok);
	printf("    Result: %s\n\n", test_status(ok));
	return (!ok);
}

static int	test_null_begin_list(size_t index)
{
	printf("[%zu] NULL begin_list\n", index);
	ft_list_sort(NULL, cmp_int);
	printf("    Result: %s\n\n", test_status(1));
	return (0);
}

/**
 * @brief Test ft_list_sort with empty, sorted, reversed, mixed and duplicate lists.
 * @return Number of failed tests.
 */
int	test_ft_list_sort(void)
{
	t_list_sort_test	tests[] = {
		{ "empty list", 0, { 0 }, { 0 } },
		{ "one node", 1, { 42 }, { 42 } },
		{ "already sorted", 10,
			{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
			{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } },
		{ "reverse order", 10,
			{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 },
			{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } },
		{ "mixed order", 10,
			{ 7, 2, 10, 1, 5, 9, 3, 8, 4, 6 },
			{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } },
		{ "duplicates", 10,
			{ 4, 2, 8, 4, 1, 2, 8, 6, 1, 6 },
			{ 1, 1, 2, 2, 4, 4, 6, 6, 8, 8 } },
		{ "negative values", 10,
			{ 0, -10, 5, -1, 3, -7, 12, -3, 8, -20 },
			{ -20, -10, -7, -3, -1, 0, 3, 5, 8, 12 } }
	};
	t_list_sort_str_test	str_test = {
		"strings with cmp_str", 10,
		{ "pear", "apple", "kiwi", "banana", "fig", "orange",
			"grape", "date", "lemon", "cherry" },
		{ "apple", "banana", "cherry", "date", "fig", "grape",
			"kiwi", "lemon", "orange", "pear" }
	};
	const size_t	n = sizeof(tests) / sizeof(tests[0]);
	int				failures = 0;

	print_test_title("FT_LIST_SORT");
	failures += test_null_begin_list(0);
	for (size_t i = 0; i < n; i++)
		failures += run_sort_case(i + 1, &tests[i]);
	failures += run_string_sort_case(n + 1, &str_test);
	return (failures);
}
