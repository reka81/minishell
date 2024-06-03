NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f

SRCS = ./environment_fs.c \
./execI.c \
./execI1.c \
./execI2.c \
./execI3.c \
./execI4.c \
./execI5.c \
./execI6.c \
./execI7.c \
./execI8.c \
./execII.c \
./execII1.c \
./execII2.c \
./execII3.c \
./expanding.c \
./expanding2.c \
./ft_isdigit.c \
./ft_lstadd_back.c \
./ft_lstadd_back2.c \
./ft_lstnew.c \
./ft_lstnew2.c \
./ft_lstsize.c \
./ft_strlen.c \
./libft_func.c \
./minishell_tools.c \
./parsing.c \
./parsing1.c \
./parsing2.c \
./redirections2.c \
./redirictions.c \
./redirictions1.c \
./redirictions3.c \
./redirictions4.c \
./rest_of_main.c \
./signals.c  \
./store_ll.c \
./store_ll2.c \
./store_ll3.c \
./store_ll4.c \
./store_ll5.c \
./store_ll6.c \
./tokenization.c \
./tokenization2.c \
./tokenization3.c \
./tokenization4.c \
./tokenization5.c \
./tokenization6.c \
./zyalloc.c 

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
