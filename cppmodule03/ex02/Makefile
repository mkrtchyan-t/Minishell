NAME = FragTrap

SRCS = FragTrap.cpp \
       ClapTrap.cpp \
       main.cpp \

OBJS = ${SRCS:.cpp=.o}

all:${NAME}

${NAME}:	${OBJS}
		g++ -Wall -Wextra -Werror -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}
fclean:	clean
	rm -f ${NAME}

re: fclean all

.PHONY:
	all clean fclean re
