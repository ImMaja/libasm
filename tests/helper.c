#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Allocate memory or abort the test runner on failure.
 * @param size Number of bytes to allocate.
 * @return Pointer to the allocated memory.
 */
void	*xmalloc(const size_t size)
{
	void	*ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "Memory allocation failed. Tests aborted\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * @brief Print a colored test section title.
 * @param title Name of the test section.
 */
void	print_test_title(const char *title)
{
	printf("\033[1;36m    ---- %s ----\033[0m\n\n", title);
}
