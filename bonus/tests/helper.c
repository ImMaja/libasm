#include <stdio.h>

/**
 * @brief Print a colored test section title.
 * @param title Name of the test section.
 */
void	print_test_title(const char *title)
{
	printf("\033[1;36m    ---- %s ----\033[0m\n\n", title);
}
