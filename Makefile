NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f

SRCS = tokenization.c ft_lstadd_back.c ft_lstnew.c ft_strlen.c ft_lstnew2.c ft_lstadd_back2.c parsing.c store_ll.c ft_isdigit.c \
	ft_lstsize.c minishell_tools.c environment_fs.c expanding.c tokenization2.c rest_of_main.c  store_ll2.c store_ll3.c store_ll4.c  redirictions.c execI1.c execI2.c execI3.c execI4.c execI5.c execI6.c execI7.c execI8.c execII1.c execI.c execII.c zyalloc.c tokenization3.c tokenization4.c tokenization5.c  \
	expanding2.c store_ll5.c redirections2.c redirictions1.c libft_func.c execII2.c parsing1.c parsing2.c signals.c
OBJS = $(SRCS:.c=.o)
DEPS = minishell.h

all : $(NAME)

$(NAME) : $(OBJS) $(DEPS)
	$(CC) $(CFLAGS)  -L /Users/mettalbi/.brew/opt/readline/lib $(OBJS) -o $(NAME) -lreadline

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I /Users/mettalbi/.brew/opt/readline/include -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all