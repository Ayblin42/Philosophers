CC			=	gcc

FLAGS		=	-Wall -Werror -Wextra -pthread -g3

RM			=	rm -f

SRCS		=	main.c \
				init.c \
				display.c \
				ft_action.c \
				utils.c \
				death_checker.c \

OBJS		=	${SRCS:.c=.o}

NAME		=	philo

all			:		${NAME}

${NAME}		:	 ${OBJS}
				${CC} ${FLAGS} ${OBJS} -o ${NAME}


.c.o		:
				${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean		:
				${RM} ${OBJS}

fclean		:	clean
				${RM} ${NAME}

re			:	fclean	all

.PHONY		:	all clean fclean re 
