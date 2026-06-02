#include <stdio.h>

#include "tests_bonus.h"

int	main(void)
{
	int	failures = 0;

	failures += test_ft_atoi_base();

	printf("\n%d test(s) failed.\n\n", failures);
	return (failures != 0);
}
