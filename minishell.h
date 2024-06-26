/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:27:01 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/14 17:33:02 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <termios.h>

# define ERROR_GETCWD "cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n"

int	g_is_in_mini;

typedef struct stack
{
	char			*value;
	int				type;
	int				should_be_exp;
	struct stack	*next;
	int				did_expand;
	char			*was;
	int				prev_is_null;
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
	int				shouldnt_run;
}	t_hxh;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_int
{
	int			out;
	int			in;
	char		*zz;
	char		*ten;
	char		**str;
	int			first_time;
	int			fd;
	int			z;
	int			k;
	int			n;
	int			i;
	char		*chen;
	char		*val;
	t_env		*env;
	int			*exit_status;
}	t_int;

typedef struct s_exec
{
	int		fd[2];
	char	**arg;
	int		ex;
	char	*variable;
	char	*value;
	char	*path;
	int		pid;
	int		*exit_status;
}	t_exec;

typedef struct s_exec1
{
	char			*value;
	char			*variable;
	char			cwd[1024];
	int				pid;
	char			*path;
	int				*pid_tab;
	int				i;
	int				num_of_elems;
	char			*path2;
	char			**env;
	int				a;
	int				*exit_status;
	struct termios	my_termios;
}	t_exec1;

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
	char	*str2;
	int		empty;
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

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

void	ft_lstadd_back(t_stack **lst, t_stack *newnode);
t_stack	*ft_lstnew(char *content, int quote_type);
int		ft_strlen1(char *s);
t_env	*ft_lstnew2(void *variable, void *value);
void	ft_lstadd_back2(t_env **lst, t_env *newnode);
int		ft_pars(char *str);
int		ds_quotes(char *str);
int		double_pipe(char *str);
int		parentheses(char *str);
t_hxh	*ft_store(t_stack *lol, t_env *environment, int *exit_status);
char	*rederection_handling(t_stack **lst, t_int *lor_int, char *chen);
char	*append(t_stack **lst, t_int *lor_int, int *i, char *chen);
void	herdog(t_stack **lst, t_int *lor_int);
char	*infile(t_stack **lst, t_int *lor_int, int *i, char *chen);
char	*rederection(t_stack **lst, t_int *lor_int, int *i, char *chen);
char	*herdog_delm(t_stack **lst, int *flag);
int		num_herdog(t_stack *lol);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
void	execution(t_env **environment, t_hxh *final_linked,
			char **env, int *exit_status);
int		ft_lstsize(t_hxh *lst);
int		ft_cheak_n(char *str);
void	ft_echo(t_hxh *lst, int *exit_status);
void	ft_exit(t_hxh *lst, int *exit_status);
void	ft_unset(t_hxh *lst, t_env **env, int *exit_status);
void	ft_putstr_fd1(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*look_for_path(char *cmd, char *path);
void	setup_signal_handlers(int *exit_status);
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
t_hxh	*ft_lstnew1(t_int *lor_int, char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		check_if_pls2(char *str);
char	*ft_strmcpy(char *path, char *value);
int		is_apath(char *str);
char	*new_var_woutpls(char *variable);
char	*new_var_woutequal(char *variable);
int		check_if_pls(char **str);
void	ft_putstr_fd2(char *s, int fd);
t_env	*check_if_var2(t_env *environment, char *variable);
t_env	*check_if_var(t_env *environment, char *variable);
int		check_if_value(char **str);
void	store_var(t_hxh *final_linked, int *i, char *variable);
void	store_val(t_hxh *final_linked, int *i, int *j, char *value);
void	join_or_n(t_hxh *final_linked, t_env *tmp, char *value);
void	afterwards_assignment(t_hxh *final_linked,
			t_env *environment, t_env *tmp);
int		check_if_equal(char *str);
void	no_args_export(t_hxh *final_linked, char **env);
void	store_var1(t_hxh *final_linked, char **variable, int *i, int *d);
void	setting_var_and_val(char **variable,
			char **value, t_hxh *final_linked, int d);
int		cmp_w_dlm(char c, char s);
int		check_if_dlm(char *str);
int		normal_exporting(char *variable, char *value,
			t_hxh *final_linked, t_env *environment);
void	no_args_export2(t_env *environment);
void	export2(t_hxh *final_linked, t_env *environment,
			t_exec *var, int *exit_status);
void	export(t_hxh *final_linked, t_env *environment,
			t_exec1 *var, int *exit_status);
char	**fill_args(t_hxh *final_linked);
void	dup_close1(t_hxh *final_linked);
void	dup_close2(t_hxh *final_linked);
void	dup_close3(int *fd);
void	expo2(t_hxh *final_linked, t_env *environment,
			t_exec *var, int *exit_status);
void	execve1(char *path, char **arg, char **env);
void	dup_close4(int *fd);
void	ecexc_cmd1(t_exec *var, t_hxh *final_linked,
			t_env *environment, char **env);
int		execute_cmds(t_hxh *final_linked, char **env,
			t_env *environment, int *exit_status);
void	pwd_cmd(t_hxh *final_linked);
void	env_cmd(t_env *environment);
void	cd_cmd(t_hxh *final_linked, t_env *environment, int *exit_status);
int		ft_cheak_n(char *str);
int		ft_strdigit(char *str);
void	ft_echo(t_hxh *lst, int *exit_status);
void	ft_exit(t_hxh *lst, int *exit_status);
void	dup_close5(int fd_out, int fd_in);
void	not_builtins(t_hxh *final_linked, t_exec1 *var,
			t_env *environment, int *exit_status);
void	join_or_not(char *value, char *variable, t_env *tmp);
void	exp_n_valid(t_hxh *final_linked, char *value);
void	ctl_c(int a);
void	*zyalloc(long long size);
void	close_fds(t_hxh *final_linked);
void	rest_of_main(t_main *main_fun, t_stack *a,
			t_env **environment, t_hxh *final_linked);
void	ft_lstadd_back7(t_env **lst, t_env *newnode);
t_env	*ft_lstnew5(char *variable, char *value);
void	clean_final2(t_hxh *final_linked, int i);
void	freeing_pr(t_stack **a);
int		check_if_null(t_stack *a);
void	ft_rm_null(t_stack **a);
char	*fill(char *str1, char *str2);
void	routine(t_stack *a, t_main *main_fun, t_env **environment,
			t_hxh *final_linked);
void	init(t_numbers *tokens);
void	rest_of_tokenization(char *str, t_numbers *tokens,
			t_stack **a, char *l);
void	rest_of_expanding2(t_stack *a, t_counter *count_num, char *str2);
void	rest_of_expanding(t_exp *expander, t_stack *a,
			char *str2, t_counter *count_num);
void	rest_of_expanding4(t_exp *expander, char *str2, t_counter *count_num);
void	rest_of_expanding3(t_stack *a, t_counter *count_num,
			t_exp *expander, t_env *environment);
void	if_next_is_space(t_stack **lst, char **splitting,
			t_int *lor_int, int *j);
void	if_next_not_space(t_stack **lst, t_int *lor_int,
			char **splitting, int *j);
void	if_next_is_null(t_stack **lst, char **splitting,
			t_int *lor_int, int *j);
char	*opening_rederections(t_stack **lst, t_int *lor_int, char *chen, int i);
int		count_word(char *s);
int		count_strings(const char *s, char c);
void	ft_unset_v1(t_env **env, t_hxh *lst, int i, t_env *tmp3);
void	one_command(t_hxh *final_linked, t_env **environment,
			t_exec1 *var, int *exit_status);
char	*ft_rm_equal(char *str);
int		not_valid(char **strs);
void	primary_pipes(t_exec1 *var, t_hxh *final_linked,
			char **env, t_env *environment);
int		pipeee(char *str, int *i, int *j);
int		rederectionnn(char *str, int *i, int *j);
int		infileee(char *str, int *i, int *j);
void	print_ambigious(t_stack *a);
char	*ft_get_env1(char *val, t_env *enviroment);
char	*new_val_woutequal(char *value);
int		more_than_two(t_stack *lst);
void	fill_env2(t_env **environment);
char	*append_open_file(t_stack **lst, int *i, t_int *lor_int, char *chen);
char	*append_open_file2(t_stack **lst, int *i, t_int *lor_int, char *chen);
char	*opening_rederections(t_stack **lst, t_int *lor_int, char *chen, int i);
void	split_or_not_split(t_stack **lst, char **splitting,
			t_int *lor_int, int *j);
void	handling_space_in_expanding(t_stack **lst, char **splitting,
			int *j, t_int *lor_int);
void	handling_dq(t_stack **lst, char **splitting, int *j, t_int *lor_int);
char	*remove_tab(char *l);
void	ft_exit2(t_hxh *lst, int *exit_status);
void	pwd_cmd2(t_hxh *final_linked);
char	*reder_chen2(t_stack **lst, t_int *lor_int, char *chen);
char	*reder_chen(t_stack **lst, t_int *lor_int, char *chen);
char	*append_chen2(t_stack **lst, t_int *lor_int, char *chen);
char	*append_chen(t_stack **lst, t_int *lor_int, char *chen);
void	last_pipe_num(t_stack **lst, int *last_pipe);
void	waiting_for_children(int fd_out, int fd_in, t_exec1 *var);
void	ft_echo2(int *i, t_hxh *lst);
int		cmp_w_dlm2(char c);
char	*expanding_her(char *value, int exit_status, t_env *environment);
void	rest_of_expanding3_her(char *value, t_counter *count_num,
			t_exp *expander, t_env *environment);
void	rest_of_expanding2_her(char *value, t_counter *count_num, char *str2);
void	rest_of_expanding_her(t_exp *expander, char *value,
			char *str2, t_counter *count_num);
void	rest_of_expanding6_her(t_counter *count_num, char *value,
			t_exp *expander, t_env *environment);
void	setting_values_her(t_exp *expander, t_counter *count_num,
			int exit_status);
void	check_str_null_her(t_exp *expander, char *value);
int		cmp_delim_her(char c);
void	rest_of_expanding5_her(char *value, t_counter *count_num, char *str2);
void	rest_of_expanding4_her(t_exp *expander, char *str2,
			t_counter *count_num);
void	tb_expanded_her(char *value, t_counter *count_num,
			char *str, t_exp *expander);
char	*file_name(t_stack **lst);
char	*str_setting(t_stack **tmp, char *str);
void	ft_echo3(t_hxh *lst, int *exit_status);
void	env_cmd2(t_env *environment, int output);
void	checking_them(t_hxh *final_linked, t_env *environment, t_exec1 *var);
void	checking_them2(t_exec *var, t_hxh *final_linked, t_env *environment);
void	ft_echo3(t_hxh *lst, int *exit_status);
void	join_or_not(char *value, char *variable, t_env *tmp);
char	*export_decision(char *variable, char *new,
			t_env **tmp, t_env *environment);
char	*find_value(t_stack *lst);
int		lenv(t_env *environment);
int		breaking_expanding(t_stack	*a);
int		ft_lstsize1(t_env *lst);
int		ft_lstsize2(t_stack *lst);
int		ft_atoi(char *str);
void	i_set(t_exp **expander, t_counter **count_num,
			int exit_status, int *flag);
void	setting_values(t_exp *expander, t_counter *count_num, int exit_status);
int		ft_lstsize3(t_hxh *lst);
int		checking_parsing(t_stack *lst);
int		break_its(t_stack **a, t_exp *expander, t_env *environment);
void	rest_of_main7(t_stack **a, t_main *main_fun, t_env **environment);
void	initing_values(t_int *lor_int, char **var, t_stack **lst);
void	charing(char **str, char **str1, t_env **env, t_env *tmp3);
#endif 
