#ifndef LIBASM_H
# define LIBASM_H

# include <stddef.h>
# include <sys/types.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buffer, size_t count);
ssize_t	ft_read(int fd, void *buffer, size_t count);
char	*strdup(const char *s);

#endif /** LIBASM_H */
