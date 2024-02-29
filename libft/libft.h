/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:54:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 15:27:10 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdbool.h>

# define TRUE 1
# define FALSE 0
# define READ_END 0
# define WRITE_END 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int					ft_isdigit(int c);
int					iswhitespace(char c);
long				ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					basamak_sayar(int n);
char				*ft_itoa(int n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *restrict dst, const void *restrict src,
						size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *c, int fd);
char				**ft_split(const char *s, char c);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strdup(const char *s1);
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_freeself(char *reamins, char *buffer);
size_t				ft_strlcat(char *restrict dst, const char *restrict src,
						size_t dstsize);
size_t				ft_strlcpy(char *restrict dst, const char *restrict src,
						size_t dstsize);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2,
						size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strcmp(char *s1, char *s2);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new_node);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new_node);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					hexatransformlower(unsigned int x);
int					hexatransformupper(unsigned int x);
int					ft_unsignednbr_fd(unsigned int x);
int					ft_printf(const char *format, ...);
int					ft_putchar_fd_print(int c, int fd);
void				ft_put3endl_fd(char *s, char *s1, char *s2, int fd);
int					ft_putnbr_fd_print(int n, int fd);
int					ft_putstr_fd_print(char *c, int fd);
size_t				ft_strlen_print(const char *s);
int					nbrprinter(int n);
int					basamak_sayar_print(unsigned int n);
int					basamak_sayar_base16(unsigned int n);
int					ft_pointerprint(unsigned long long n);
int					hexatransformlowerpointer(unsigned long long n);
char				*get_next_line(int fd);

#endif
