NAME = DiamondTrap

SRCS = FragTrap.cpp \
       ClapTrap.cpp \
       ScavTrap.cpp \
       DiamondTrap.cpp \
       main.cpp \

OBJS = ${SRCS:.cpp=.o}

all:${NAME}

${NAME}:	${OBJS}
		g++ -Wall -Wextra -Werror -Wno-shadow -Wshadow -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}
fclean:	clean
	rm -f ${NAME}

re: fclean all

.PHONY:
	all clean fclean re
