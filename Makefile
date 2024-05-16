NAME = minishell
cc = CC
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRCS = tokenization.c ft_lstadd_back.c ft_lstnew.c ft_strlen.c  ft_lstnew2.c ft_lstadd_back2.c parsing.c store_ll.c ft_isdigit.c execution.c execution2.c \
		ft_lstsize.c minishell_tools.c signals.c environment_fs.c expanding.c tokenization2.c rest_of_main.c  store_ll2.c store_ll3.c store_ll4.c  redirictions.c
OBJS = $(SRCS:.c=.o)
all : $(NAME)


$(NAME) : $(OBJS) $(minishell.h)
	$(CC) $(CFLAGS) -I/Users/mettalbi/.brew/Cellar/readline/8.2.10/include -L/Users/mettalbi/.brew/Cellar/readline/8.2.10/lib $(OBJS) -o $(NAME)

%.o:%.c minishell.h
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all