CC			=	gcc

FLAGS		=	-Wall -Werror -Wextra -pthread -g3

RM			=	rm -f

SRCS		=	main.c \
				init.c \
				display.c \

OBJS		=	${SRCS:.c=.o}

LIBS		=	-lreadline

LIBFT		=	libft/libft.a

NAME		=	philo

all			:	${LIBFT}	${NAME}

${NAME}		:	${LIBFT} ${OBJS}
				${CC} ${FLAGS} ${OBJS} ${LIBFT} ${LIBS} -o ${NAME}

${LIBFT}	:
				make -C libft/ bonus

.c.o		:
				${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean		:
				${RM} ${OBJS}
				make -C libft/ clean

fclean		:	clean
				${RM} ${NAME}
				make -C libft/ fclean

re			:	fclean	all

.PHONY		:	all clean fclean re libft
