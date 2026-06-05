#include <stdio.h>

#include "tests_bonus.h"

int	main(void)
{
	int	failures = 0;

	failures += test_ft_atoi_base();
	failures += test_ft_list_push_front();
	failures += test_ft_list_size();
	failures += test_ft_list_sort();

	printf("\n%d test(s) failed.\n\n", failures);
	return (failures != 0);
}
