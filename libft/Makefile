# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arastepa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/23 12:43:16 by arastepa          #+#    #+#              #
#    Updated: 2021/01/30 15:07:55 by arastepa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memset.c	\
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strcmp.c \
		ft_isspace.c

SRCS_B = ft_lstnew.c \
		 ft_lstadd_front.c \
		 ft_lstsize.c \
		 ft_lstlast.c \
		 ft_lstadd_back.c \
		 ft_lstdelone.c \
		 ft_lstclear.c \
		 ft_lstiter.c \
		 ft_lstmap.c \

OBJS	= 	${SRCS:.c=.o}

OBJS_B	=	$(SRCS_B:.c=.o)

RM		=	rm -f

LIBC	= ar -rcs

CFLAGS	=	-Wall -Wextra -Werror

INCS	= .

.c.o:		
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCS}

$(NAME):	${OBJS}
			${LIBC} $(NAME) $(OBJS)

all:		$(NAME)

bonus:		$(NAME) $(OBJS_B)
			${LIBC} $(NAME) $(OBJS_B)

clean:		
			$(RM) -f $(OBJS) $(OBJS_B)

fclean:		clean
			$(RM) $(NAME) $(bonus)

re:			fclean all

.PHONY:		all bonus clean fclean re .c.o
