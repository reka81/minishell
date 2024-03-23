#include "minishell.h"

static char	*ft_char(char *s, unsigned int number, long int len)
{
	while (number > 0)
	{
		s[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (s);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char				*s;
	long int			len;
	unsigned int		number;

	len = ft_len(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!(s))
		return (NULL);
	s[len--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		number = n * -1;
		s[0] = '-';
	}
	else
		number = n;
	s = ft_char(s, number, len);
	return (s);
}
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src [i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

static	int	count_strings(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
    if(!s)
        return(0);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static void	*ft_free(char **strs, int i)
{
	while (i--)
		free(strs[i]);
	free(strs);
	return (NULL);
}

static	char	**fill_words(char **str, const char *s, char c, int count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[j] && i < count)
	{
		len = 0;
		while (s[j] == c && s[j])
			j++;
		while (s[j + len] != c && s[j + len])
			len++;
		if (len != 0)
		{
			str[i] = malloc((len + 1) * sizeof(char));
			if (!str[i])
				return (ft_free(str, i));
			ft_strlcpy(str[i], (s + j), len + 1);
			j = j + len;
			i++;
		}
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	str = NULL;
    str = malloc((count_strings(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
    if (!s)
	{
        *str = NULL;
		return (str);
	}
	return (fill_words(str, s, c, count_strings(s, c)));
}

// t_stack	*ft_lstlast(t_stack *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }
// void	ft_lstadd_back(t_stack **lst, t_stack *new)
// {
// 	if (!lst || !new)
// 		return ;
// 	if (*lst)
// 		ft_lstlast(*lst)->next = new;
// 	else
// 		*lst = new;
// }

t_hxh	*ft_lstnew1(char **content, int out, int in)
{
	t_hxh	*new_node;

	new_node = malloc(sizeof(t_hxh));
    if (!new_node)
		return (NULL);
    new_node->value = content;
    new_node->output = out;
    new_node->input = in;
	new_node->next = NULL;
	return (new_node);
}

t_hxh	*ft_lstlast1(t_hxh *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
void	ft_lstadd_back1(t_hxh **lst, t_hxh *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast1(*lst)->next = new;
	else
		*lst = new;
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
    write(fd, "\n", 1);
}
int num_herdog(t_stack *lol)
{
    t_stack *tmp = lol;
    int count = 0;
    while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
    {
        if (ft_strcmp(tmp->value, "<<") == 0)
        {
            count++;
        }
        tmp = tmp->next;
    }
    return (count);
}
char *herdog_delm(t_stack *lst)
{
    t_stack *tmp = lst;
    
    while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
    {
        if (ft_strcmp(tmp->value, "<<") == 0)
        {
            if (tmp->next->type == 6)
                return (tmp->next->next->value);
            return (tmp->next->value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}
void rederection(t_stack **lst, int *in, int *out, int *fd)
{
    if (ft_strcmp((*lst)->value, ">") == 0)
    {
        if ((*lst)->next->type == 6)
        {
            if (*out == 3)
                close(*fd);
            *fd = open((*lst)->next->next->value, O_CREAT | O_RDWR , 0644);
        }
        else
        {
            if (*out == 3)
                close(*fd);
            *fd = open((*lst)->next->value, O_CREAT | O_RDWR , 0644);
        }
        *out = *fd;
        if ((*lst)->next->type == 6)
            (*lst) = (*lst)->next->next;
        else
            (*lst) = (*lst)->next;
    }
}

char *infile(t_stack **lst, int *fd, int *in, int *out)
{
    char *chen = NULL;
    if (ft_strcmp((*lst)->value, "<") == 0)
    {
        if ((*lst)->next->type == 6)
        {
            if (access((*lst)->next->next->value, F_OK) == 0)
            {
                if (*in >= 3)
                    close(*fd);
                *fd = open((*lst)->next->next->value, O_RDWR, 0644);
                *in = *fd;
            }
            else
                chen = "No such file or directory";
        }
        else
        {
            if (access((*lst)->next->value, F_OK) == 0)
            {
                if (*in >= 3)
                    close(*fd);
                *fd = open((*lst)->next->value, O_RDWR, 0644);
                *in = *fd;
            }
            else
                chen = "No such file or directory";
        }
        if ((*lst)->next->type == 6)
            (*lst) = (*lst)->next->next;
        else
            (*lst) = (*lst)->next;
    }
    return (chen);
}
void herdog(t_stack **lst, int *fd , t_int *lor_int, int *n)
{
    char *ll = NULL;

    // printf("ss\n");
    if (ft_strcmp((*lst)->value, "<<") == 0)
    {
        lor_int->ten = ft_strjoin("file", ft_itoa(*n));
        if (lor_int->in >= 3)
            close(*fd);
        *fd = open(lor_int->ten, O_CREAT | O_RDWR | O_TRUNC, 0644);
        while (1)
        {
            ll = readline (">");
            if (!ll)
                exit(1);
            lor_int->zz = herdog_delm(*lst);
            if (ft_strcmp(lor_int->zz, ll) == 0)
                break;
            ft_putstr_fd(ll, *fd);
        }
        (*n)++;
        lor_int->in = *fd;
        if ((*lst)->next->type == 6)
            (*lst) = (*lst)->next->next;
        else
            (*lst) = (*lst)->next;
    }
}

void append(t_stack **lst, int *fd, t_int *lor_int)
{
    if(ft_strcmp((*lst)->value, ">>") == 0)  
    {
        if ((*lst)->next->type == 6)
        {
            if (lor_int->out == 3)
                close(*fd);
            *fd = open((*lst)->next->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
        }
        else
        {
            if (lor_int->out == 3)
                close(*fd);
            *fd = open((*lst)->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
        }
        lor_int->out  = *fd;
        if ((*lst)->next->type == 6)
            (*lst) = (*lst)->next->next;
        else
            (*lst) = (*lst)->next;
    }
}

char *rederection_handling(t_stack **lst, int n, t_int *lor_int, char *chen)
{
    if (*lst != NULL && ((*lst)->type == 1 || (*lst)->type == 2 || (*lst)->type == 0))
    {
        lor_int->str[lor_int->z] = (*lst)->value;
        lor_int->z++;
    }
    else if (*lst != NULL && (*lst)->type == 3)
    {
        rederection(lst, &lor_int->in, &lor_int->out, &lor_int->fd);
        chen = infile(lst, &lor_int->fd, &lor_int->in, &lor_int->out);
        herdog(lst , &lor_int->fd, lor_int, &n);
        append(lst, &lor_int->fd, lor_int);
    }
    return(chen);
}

t_hxh *ft_store(t_stack *lol)
{
    t_hxh *l;
    char *ll;
    int i = 0;
    t_int *lor_int = malloc(sizeof(t_int));
    int n = 1;
    char *chen = NULL;
    t_stack *lst;
    
    i = 0;
    n = 1;
    chen = NULL;
    lst = lol;
    l = NULL;
    lor_int = malloc(sizeof(t_int));
    while (lst != NULL)
    {
        lor_int->str = malloc(sizeof(char *) * 100);
        lor_int->out = 1;
        lor_int->in = 0;
        lor_int->fd = 0;
        lor_int->z = 0;
        while (lst != NULL && ft_strcmp(lst->value, "|") != 0)
        {
            chen = rederection_handling(&lst, n, lor_int, chen);
            lst = lst->next;
            if(lst == NULL)
                break;
        }
        lor_int->str[lor_int->z] = NULL;
        ft_lstadd_back1(&l, ft_lstnew1(lor_int->str, lor_int->out, lor_int->in));
        if(lst == NULL)
            break;
        lst = lst->next;
    }
    if (chen != NULL)
        printf("%s\n",chen);
    return (l);
}
