#include <stddef.h>

typedef struct s_list
{
 void *content;
 struct s_list	*next;
} t_list;

#define STUB __attribute__((weak))

STUB void ft_bzero(void *s, size_t n)
{
	(void)s;
	(void)n;
}

STUB char *ft_strrchr(const char *s, int c)
{
	(void)s;
	(void)c;
	return (0);
}

STUB char *ft_strchr(const char *s, int c)
{
	(void)s;
	(void)c;
	return (0);
}
STUB char *ft_strnstr(const char *b, const char *l, size_t n)
{
	(void)b;
	(void)l;
	(void)n;
	return (0);
}
STUB size_t ft_strlcpy(char *d, const char *s, size_t n)
{
	(void)d;
	(void)s;
	(void)n;
	return (0);
}
STUB size_t ft_strlcat(char *d, const char *s, size_t n)
{
	(void)d;
	(void)s;
	(void)n;
	return (0);
}
STUB int ft_isalnum(int c)
{
	(void)c;
	return (0);
}
STUB int ft_isalpha(int c)
{
	(void)c;
	return (0);
}
STUB int ft_isascii(int c)
{
	(void)c;
	return (0);
}
STUB int ft_isdigit(int c)
{
	(void)c;
	return (0);
}
STUB int ft_isprint(int c)
{
	(void)c;
	return (0);
}
STUB size_t ft_strlen(const char *s)
{
	(void)s;
	return (0);
}
STUB int ft_strncmp(const char s1[], const char s2[], size_t n)
{
	(void)s1;
	(void)s2;
	(void)n;
	return (0);
}
STUB int ft_atoi(char *s)
{
	(void)s;
	return (0);
}
STUB int ft_tolower(int c)
{
	(void)c;
	return (0);
}
STUB int ft_toupper(int c)
{
	(void)c;
	return (0);
}
STUB void *ft_memchr(const void *s, int c, size_t n)
{
	(void)s;
	(void)c;
	(void)n;
	return (0);
}
STUB int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	(void)s1;
	(void)s2;
	(void)n;
	return (0);
}
STUB void *ft_memcpy(void *d, const void *s, size_t n)
{
	(void)d;
	(void)s;
	(void)n;
	return (0);
}
STUB void *ft_memmove(void *d, const void *s, size_t n)
{
	(void)d;
	(void)s;
	(void)n;
	return (0);
}
STUB void *ft_memset(void *s, int c, size_t n)
{
	(void)s;
	(void)c;
	(void)n;
	return (0);
}
STUB char *ft_strdup(const char *s)
{
	(void)s;
	return (0);
}
STUB void *ft_calloc(size_t n, size_t s)
{
	(void)n;
	(void)s;
	return (0);
}
STUB char *ft_substr(char const *s, unsigned int i, size_t l)
{
	(void)s;
	(void)i;
	(void)l;
	return (0);
}
STUB char *ft_strjoin(char const *s1, char const *s2)
{
	(void)s1;
	(void)s2;
	return (0);
}
STUB char *ft_strtrim(char const *s1, char const *s)
{
	(void)s1;
	(void)s;
	return (0);
}
STUB char **ft_split(char const *s, char c)
{
	(void)s;
	(void)c;
	return (0);
}
STUB char *ft_itoa(int n)
{
	(void)n;
	return (0);
}
STUB char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	(void)s;
	(void)f;
	return (0);
}
STUB void ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	(void)s;
	(void)f;
}
STUB void ft_putchar_fd(char c, int fd)
{
	(void)c;
	(void)fd;
}
STUB void ft_putstr_fd(char *s, int fd)
{
	(void)s;
	(void)fd;
}
STUB void ft_putendl_fd(char *s, int fd)
{
	(void)s;
	(void)fd;
}
STUB void ft_putnbr_fd(int n, int fd)
{
	(void)n;
	(void)fd;
}
STUB t_list *ft_lstnew(void *c)
{
	(void)c;
	return (0);
}
STUB void ft_lstadd_front(t_list **l, t_list *n)
{
	(void)l;
	(void)n;
}
STUB int ft_lstsize(t_list *l)
{
	(void)l;
	return (0);
}
STUB t_list *ft_lstlast(t_list *l)
{
	(void)l;
	return (0);
}
STUB void ft_lstadd_back(t_list **l, t_list *n)
{
	(void)l;
	(void)n;
}
STUB void ft_lstdelone(t_list *l, void (*d)(void *))
{
	(void)l;
	(void)d;
}
STUB void ft_lstclear(t_list **l, void (*d)(void *))
{
	(void)l;
	(void)d;
}
STUB void ft_lstiter(t_list *l, void (*f)(void *))
{
	(void)l;
	(void)f;
}
STUB t_list *ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *))
{
	(void)l;
	(void)f;
	(void)d;
	return (0);
}
