NAME = animal

WRONG = wrong

SRCS = Animal.cpp \
       Cat.cpp \
       Dog.cpp \
       main.cpp \

WRONGSRCS = WrongAnimal.cpp \
			WrongCat.cpp \
			wrongmain.cpp \

OBJS = ${SRCS:.cpp=.o}

WRONGOBJS = ${WRONGSRCS:.cpp=.o}

all:${NAME}

${NAME}:	${OBJS}
		g++ -Wall -Wextra -Werror -o ${NAME} ${OBJS}

${WRONG}:	${WRONGOBJS}
		g++ -Wall -Wextra -Werror -o ${WRONG} ${WRONGOBJS}

clean:
	rm -f ${OBJS}
	rm -f ${WRONGOBJS}
fclean:	clean
	rm -f ${NAME}
	rm -f ${WRONG}

re: fclean all

.PHONY:
	all clean fclean re
