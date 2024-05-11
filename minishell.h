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

typedef struct s_counter
{
    int i;
    int j;
    int d;
    int e;
    int k;
}   t_counter;

typedef struct s_forexpand
{
    char *user;
    int exit_to_expand;
    int dollar_flag;
    int exit_status;
}   t_exp;

typedef struct s_numbers
{
    int i;
    int j;
    int quote_flag;
    int flag_for_white;
}   t_numbers;

typedef struct s_main
{
    char *buf;
    char *old_path;
    char *current_path;
    char **envi2;
    int save_fd;
    char *l;
}   t_main;

typedef struct s_fillingenv
{
    char *value;
    char *variable;
    int e;
    int i;
    int j;
}   t_filling_env;

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
void    ft_unset(t_hxh *lst, t_env **env, int *exit_status);
void    ft_putstr_fd1(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*look_for_path(char *cmd, char *path);
void setup_signal_handlers();
char **store_env_2darr(t_env *environment);
char *ft_get_env(char *var, t_env *enviroment);
char *new_var_woutequal(char *variable);
char	*ft_itoa(int n);
void expanding(t_stack *a, int exit_status, t_env *environment);
int cmp_delim(char c);
void tokenization(t_stack **a, char *l);
void	flaging_expandables(t_stack *a);
int cmp_delim(char c);
void	filling_env2(t_filling_env *fill, char **env);
void filling_env(char **env, t_env **environment);
char *ft_update_pwd(t_env *environment, char *current_path, char *old_path);
int check_if_equal(char *str);
void	ft_lstadd_back1(t_hxh **lst, t_hxh *new);
t_hxh	*ft_lstnew1(char **content, int out, int in);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);

#endif 