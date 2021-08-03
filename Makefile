NAME = minishell

SRCS =	init.c \
		minishell.c \
		quotes.c \
		execve.c \
		builtins.c \
		messages.c \
		checkredirects.c \
		utils.c \
		utils2.c \
		echo.c \
		unset.c \
		cdpwdenv.c \
		export.c \
		free.c \
		utils3.c

LIBFT		= ./libft/libft.a

OBJS = ${SRCS:.c=.o}

RM	= rm -rf

LDFLAGS = -L/Users/$$(whoami)/.brew/opt/readline/lib
CPPFLAGS = -I/Users/$$(whoami)/.brew/opt/readline/include

GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0;0m

.c.o:
		@gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

all: ${LIBFT} ${NAME}

${LIBFT}:
		@make -C ./libft --silent
		@echo "$(GREEN) libft.a	created! $(RESET)"

${NAME}: $(OBJS)
		@gcc $(CPPFLAGS) $(LDFLAGS) $(LIBFT) -lreadline -Wall -Wextra -Werror -o $@ ${OBJS}
		@echo "$(GREEN) $(NAME)	created! $(RESET)"
		@echo "$(GREEN) objects	created! $(RESET)"

clean:
	@make -C ./libft clean --silent
	@$(RM) $(OBJS) --silent
	@echo "$(RED) libft.a	deleted! $(RESET)"
	@echo "$(RED) objectcs	deleted! $(RESET)"


fclean: clean
	@$(RM) $(NAME) --silent
	@$(RM) $(LIBFT) --silent
	@echo "$(RED) $(NAME)	deleted! $(RESET)"

re:	fclean all

.PHONY: all clean fclean re