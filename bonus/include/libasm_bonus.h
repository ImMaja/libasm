#ifndef LIBASM_BONUS_H
# define LIBASM_BONUS_H

# include <stddef.h>
# include <sys/types.h>

/** t_list struct declaration */
typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

int		ft_atoi_base(char *str, char *base);
void	ft_list_push_front(t_list **begin_list, void *data);

#endif /** LIBASM_BONUS_H */
