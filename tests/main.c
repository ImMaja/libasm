#include <stdio.h>

#include "tests.h"

int	main(void)
{
	int	failures = 0;

	failures += test_ft_strlen();
	failures += test_ft_strcpy();
	failures += test_ft_strcmp();

	printf("\n%d test(s) failed.\n\n", failures);
	return (failures != 0);
}
