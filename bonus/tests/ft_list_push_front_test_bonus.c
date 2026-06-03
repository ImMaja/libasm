#include <stdio.h>
#include <stdlib.h>

#include "../include/libasm_bonus.h"
#include "tests_bonus.h"

void	ft_list_push_front(t_list **begin_list, void *data);

static const char	*test_status(int ok)
{
	if (ok)
		return ("OK");
	return ("KO");
}

static void	print_bool_check(const char *label, int ok)
{
	printf("    %-18s: %s\n", label, test_status(ok));
}

static void	print_ptr_check(const char *label, const void *expected,
	const void *actual)
{
	printf("    %-18s: expected %p | actual %p | %s\n", label,
		(void *)expected, (void *)actual, test_status(expected == actual));
}

static int	test_empty_list(size_t index)
{
	t_list	*list = NULL;
	char	data[] = "first";
	int		head_created;
	int		data_ok;
	int		next_ok;
	int		ok;

	ft_list_push_front(&list, data);
	head_created = list != NULL;
	data_ok = head_created && list->data == data;
	next_ok = head_created && list->next == NULL;
	ok = head_created && data_ok && next_ok;
	printf("[%zu] push into empty list\n", index);
	print_bool_check("head created", head_created);
	print_ptr_check("data pointer", data, head_created ? list->data : NULL);
	print_ptr_check("next pointer", NULL, head_created ? list->next : NULL);
	printf("    Result: %s\n\n", test_status(ok));
	free(list);
	return (!ok);
}

static int	test_existing_list(size_t index)
{
	char	tail_data[] = "tail";
	char	old_data[] = "old head";
	t_list	tail = { tail_data, NULL };
	t_list	old_head = { old_data, &tail };
	t_list	*list = &old_head;
	char	data[] = "new head";
	t_list	*new_node;
	int		head_ok;
	int		data_ok;
	int		next_ok;
	int		old_list_ok;
	int		ok;

	ft_list_push_front(&list, data);
	new_node = list;
	head_ok = new_node != NULL && new_node != &old_head && new_node != &tail;
	data_ok = head_ok && new_node->data == data;
	next_ok = head_ok && new_node->next == &old_head;
	old_list_ok = old_head.data == old_data && old_head.next == &tail
		&& tail.data == tail_data && tail.next == NULL;
	ok = head_ok && data_ok && next_ok && old_list_ok;
	printf("[%zu] push before existing list\n", index);
	print_bool_check("head updated", head_ok);
	print_ptr_check("data pointer", data, head_ok ? new_node->data : NULL);
	print_ptr_check("next pointer", &old_head, head_ok ? new_node->next : NULL);
	print_bool_check("old list kept", old_list_ok);
	printf("    Result: %s\n\n", test_status(ok));
	if (head_ok)
		free(new_node);
	return (!ok);
}

static int	test_multiple_pushes(size_t index)
{
	t_list	*list = NULL;
	char	first_data[] = "first";
	char	second_data[] = "second";
	t_list	*first_node;
	t_list	*second_node;
	int		nodes_created;
	int		head_data_ok;
	int		head_next_ok;
	int		first_node_ok;
	int		ok;

	ft_list_push_front(&list, first_data);
	first_node = list;
	ft_list_push_front(&list, second_data);
	second_node = list;
	nodes_created = first_node != NULL && second_node != NULL
		&& first_node != second_node;
	head_data_ok = nodes_created && second_node->data == second_data;
	head_next_ok = nodes_created && second_node->next == first_node;
	first_node_ok = first_node != NULL && first_node->data == first_data
		&& first_node->next == NULL;
	ok = nodes_created && head_data_ok && head_next_ok && first_node_ok;
	printf("[%zu] push twice into list\n", index);
	print_bool_check("nodes created", nodes_created);
	print_ptr_check("head data", second_data,
		nodes_created ? second_node->data : NULL);
	print_ptr_check("head next", first_node,
		nodes_created ? second_node->next : NULL);
	print_bool_check("first node kept", first_node_ok);
	printf("    Result: %s\n\n", test_status(ok));
	if (second_node != NULL && second_node != first_node)
		free(second_node);
	free(first_node);
	return (!ok);
}

static int	test_null_data(size_t index)
{
	t_list	old_head = { "old head", NULL };
	t_list	*list = &old_head;
	t_list	*new_node;
	int		head_ok;
	int		data_ok;
	int		next_ok;
	int		ok;

	ft_list_push_front(&list, NULL);
	new_node = list;
	head_ok = new_node != NULL && new_node != &old_head;
	data_ok = head_ok && new_node->data == NULL;
	next_ok = head_ok && new_node->next == &old_head;
	ok = head_ok && data_ok && next_ok;
	printf("[%zu] push NULL data\n", index);
	print_bool_check("head updated", head_ok);
	print_ptr_check("data pointer", NULL, head_ok ? new_node->data : NULL);
	print_ptr_check("next pointer", &old_head, head_ok ? new_node->next : NULL);
	printf("    Result: %s\n\n", test_status(ok));
	if (head_ok)
		free(new_node);
	return (!ok);
}

/**
 * @brief Test ft_list_push_front node creation and list links.
 * @return Number of failed tests.
 */
int	test_ft_list_push_front(void)
{
	int	failures = 0;

	print_test_title("FT_LIST_PUSH_FRONT");
	failures += test_empty_list(0);
	failures += test_existing_list(1);
	failures += test_multiple_pushes(2);
	failures += test_null_data(3);
	return (failures);
}
