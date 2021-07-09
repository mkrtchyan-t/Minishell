NAME = minishell

SRCS = libft/ft_strlen.c \
		libft/ft_memcpy.c \
		libft/ft_split.c \
		libft/ft_strdup.c \
		init.c \
		minishell.c \

OBJS = ${SRCS:.c=.o}

RM 	 = rm -f

LDFLAGS = -L/Users/arastepa/.brew/opt/readline/lib
CPPFLAGS = -I/Users/arestepa/.brew/opt/readline/include

.c.o:
		gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

${NAME}: $(OBJS)
	 	gcc $(CPPFLAGS) $(LDFLAGS) -lreadline -Wall -Wextra -Werror -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re