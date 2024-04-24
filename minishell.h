#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <fcntl.h>

typedef struct stack
{
	char	*value;
	int		type;
    int		should_be_exp;
	struct stack *next;
}t_stack;

typedef struct s_hxh
{
    char    **value;   
    struct s_hxh   *next;
    int     output;
    int     input;
    int     flag;
}    t_hxh;

typedef struct s_env
{
    char *variable;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_int
{
    int out;
    int in;
    char *zz;
    char *ten;
    char **str;
    int first_time;
    int fd;
    int z;
}   t_int;

void	ft_lstadd_back(t_stack **lst, t_stack *newnode);
t_stack	*ft_lstnew(char *content, int quote_type);
int	ft_strlen1(char *s);
t_env	*ft_lstnew2(void *variable, void *value);
void	ft_lstadd_back2(t_env **lst, t_env *newnode);
int ft_pars(char *str);
int ds_quotes(char *str);
int double_pipe(char *str);
int parentheses(char *str);
t_hxh *ft_store(t_stack *lol);
char *rederection_handling(t_stack **lst, int n, t_int *lor_int, char *chen);
void append(t_stack **lst, int *fd, t_int *lor_int);
void herdog(t_stack **lst, int *fd , t_int *lor_int, int *n);
char *infile(t_stack **lst, int *fd, int *in, int *out);
void rederection(t_stack **lst, int *in, int *out, int *fd);
char *herdog_delm(t_stack *lst);
int num_herdog(t_stack *lol);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strcmp(char *s1, char *s2);
int ft_isdigit(int c);
void execution(t_env *environment, t_hxh *final_linked ,char **env, int *exit_status);
int	ft_lstsize(t_hxh *lst);
int    ft_cheak_n(char *str);
void    ft_echo(t_hxh *lst);
void    ft_exit(t_hxh *lst);
void    ft_unset(t_hxh *lst, t_env **env);
void    ft_putstr_fd1(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*look_for_path(char *cmd, char *path);
void setup_signal_handlers();
char **store_env_2darr(t_env *environment);
char *ft_get_env(char *var, t_env *enviroment);
char *new_var_woutequal(char *variable);
char	*ft_itoa(int n);

#endif 