#ifndef TESTS_H
# define TESTS_H

# include <stdlib.h>

/** xmalloc helper definition */
void	*xmalloc(const size_t size);

/** title printer definition */
void	print_test_title(const char *title);

/** tests functions definitions */
int	test_ft_strlen(void);
int	test_ft_strcpy(void);
int	test_ft_strcmp(void);
int	test_ft_write(void);
int	test_ft_read(void);
int	test_ft_strdup(void);

#endif /** TESTS_H */
