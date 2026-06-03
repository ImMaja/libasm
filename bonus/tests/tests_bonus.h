#ifndef TESTS_BONUS_H
# define TESTS_BONUS_H

/** title printer definition */
void	print_test_title(const char *title);

/** t_list struct declaration */
typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

/** tests functions definitions */
int	test_ft_atoi_base(void);
int	test_ft_list_push_front(void);

#endif /** TESTS_BONUS_H */
