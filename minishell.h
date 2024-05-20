/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:27:01 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/18 16:51:15 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
#include <termios.h>


typedef struct stack
{
	char			*value;
	int				type;
	int				should_be_exp;
	struct stack	*next;
	int				did_expand;
}	t_stack;

typedef struct s_hxh
{
	char			**value;
	struct s_hxh	*next;
	int				output;
	int				input;
	int				flag;
	int				is_faulty;
	int				ambigious;
}	t_hxh;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_int
{
	int		out;
	int		in;
	char	*zz;
	char	*ten;
	char	**str;
	int		first_time;
	int		fd;
	int		z;
}	t_int;

typedef struct s_exec
{
    int fd[2];
    char **arg;
    int ex;
    char *variable;
    char *value;
    char *path;
    int pid;
} t_exec;

typedef struct s_exec1
{
	// int s1;
	// int s2;
    char *value;
    char *variable;
    char cwd[1024];
    int pid;
    char *path;
    int *pid_tab;
    int i;
    int num_of_elems;
    char *path2;
    char **env;
    int a;
    int *exit_status;
	struct termios my_termios;
} t_exec1;

typedef struct s_counter
{
	int	i;
	int	j;
	int	d;
	int	e;
	int	k;
}	t_counter;

typedef struct s_forexpand
{
	char	*user;
	int		exit_to_expand;
	int		dollar_flag;
	int		exit_status;
}	t_exp;

typedef struct s_numbers
{
	int	i;
	int	j;
	int	quote_flag;
	int	flag_for_white;
}	t_numbers;

typedef struct s_main
{
	char	*buf;
	char	*old_path;
	char	*current_path;
	char	**envi2;
	int		save_fd;
	char	*l;
	int		exit_status;
}	t_main;

typedef struct s_fillingenv
{
	char	*value;
	char	*variable;
	int		e;
	int		i;
	int		j;
}	t_filling_env;

typedef struct s_store
{
	int		i;
	int		n;
	char	*chen;
}	t_store;

void	ft_lstadd_back(t_stack **lst, t_stack *newnode);
t_stack	*ft_lstnew(char *content, int quote_type);
int		ft_strlen1(char *s);
t_env	*ft_lstnew2(void *variable, void *value);
void	ft_lstadd_back2(t_env **lst, t_env *newnode);
int		ft_pars(char *str);
int		ds_quotes(char *str);
int		double_pipe(char *str);
int		parentheses(char *str);
t_hxh	*ft_store(t_stack *lol);
char	*rederection_handling(t_stack **lst, int n, t_int *lor_int, char *chen, int *i);
void	append(t_stack **lst, int *fd, t_int *lor_int, int *i);
void	herdog(t_stack **lst, int *fd, t_int *lor_int, int *n, int *i);
char	*infile(t_stack **lst, int *fd, int *in, int *out, int *i);
void	rederection(t_stack **lst, int *in, int *out, int *fd, int *i);
char	*herdog_delm(t_stack *lst);
int		num_herdog(t_stack *lol);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
void	execution(t_env *environment, t_hxh *final_linked,
			char **env, int *exit_status);
int		ft_lstsize(t_hxh *lst);
int		ft_cheak_n(char *str);
void	ft_echo(t_hxh *lst);
void	ft_exit(t_hxh *lst);
void	ft_unset(t_hxh *lst, t_env **env, int *exit_status);
void	ft_putstr_fd1(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*look_for_path(char *cmd, char *path);
void	setup_signal_handlers();
char	**store_env_2darr(t_env *environment);
char	*ft_get_env(char *var, t_env *enviroment);
char	*new_var_woutequal(char *variable);
char	*ft_itoa(int n);
void	expanding(t_stack *a, int exit_status, t_env *environment);
int		cmp_delim(char c);
void	tokenization(t_stack **a, char *l);
void	flaging_expandables(t_stack *a);
int		cmp_delim(char c);
void	filling_env2(t_filling_env *fill, char **env);
void	filling_env(char **env, t_env **environment);
char	*ft_update_pwd(t_env *environment, char *current_path, char *old_path);
int		check_if_equal(char *str);
void	ft_lstadd_back1(t_hxh **lst, t_hxh *new);
t_hxh	*ft_lstnew1(char **content, int out, int in, char *str, int i);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int check_if_pls2(char *str);
char *ft_strmcpy(char *path, char *value);
int is_apath(char *str);
char *new_var_woutpls(char *variable);
char *new_var_woutequal(char *variable);
int check_if_pls(char **str);
void ft_putstr_fd2(char *s, int fd);
t_env *check_if_var2(t_env *environment, char *variable);
t_env *check_if_var(t_env *environment, char *variable);
int check_if_value(char **str);
void store_var(t_hxh *final_linked, int *i, char *variable);
void store_val(t_hxh *final_linked, int *i, int *j, char *value);
void join_or_n(t_hxh *final_linked, t_env *tmp, char *value);
void afterwards_assignment(t_hxh *final_linked, t_env *environment, t_env *tmp);
int check_if_equal(char *str);
void no_args_export(t_env *environment, t_hxh *final_linked);
void store_var1(t_hxh *final_linked, char **variable, int *i, int *d);
void setting_var_and_val(char **variable, char **value, t_hxh *final_linked, int d);
int cmp_w_dlm(char c, char s);
int check_if_dlm(char *str);
void normal_exporting(char *variable, char *value, t_hxh *final_linked, t_env *environment);
void no_args_export2(t_env *environment, t_hxh *final_linked);
void export2(t_hxh *final_linked, t_env *environment, char *variable, char *value);
void export(t_hxh *final_linked, t_env *environment, char *variable, char *value);
char **fill_args(t_hxh *final_linked);
void dup_close1(t_hxh *final_linked);
void dup_close2(t_hxh *final_linked);
void dup_close3(int *fd);
void expo2(t_hxh *final_linked, t_env *environment, char *variable, char *value);
void execve1 (char *path, char **arg, char **env);
void dup_close4(int *fd);
void ecexc_cmd1(t_exec *var, t_hxh *final_linked, t_env *environment, char **env);
int execute_cmds(t_hxh *final_linked, char **env, t_env *environment);
void pwd_cmd(t_hxh *final_linked);
void env_cmd(t_env *environment);
void cd_cmd(t_hxh *final_linked, t_env *environment);
int    ft_cheak_n(char *str);
int    ft_strdigit(char *str);
void    ft_echo(t_hxh *lst);
void    ft_exit(t_hxh *lst);
void dup_close5(int fd_out, int fd_in);
void not_builtins(t_hxh *final_linked, t_exec1 *var, t_env *environment, int *exit_status);
void join_or_not(char *value, char *variable, char *new, t_env *tmp);
void exp_n_valid(t_hxh *final_linked, char *value);
void	ctl_c(int a);

#endif 
