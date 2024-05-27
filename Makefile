CLIENT_SRCS = client.c minitalk_utils_1.c

SERVER_SRCS = server.c minitalk_utils_1.c minitalk_utils_2.c

CLIENT_BONUS_SRCS = client_bonus.c minitalk_utils_1.c

CLIENT_BONUS_SRCS = server_bonus.c minitalk_utils_1.c minitalk_utils_2.c

OBJS = ${SRCS:.c=.o}

NAME_CLIENT = client

NAME_SERVER = server

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror


${NAME_SERVER} :  ${OBJS}
					${CC} ${CFLAGS} ${SERVER_SRCS} -o ${NAME_SERVER}

${NAME_CLIENT} :  ${OBJS}
					${CC} ${CFLAGS} ${CLIENT_SRCS} -o ${NAME_CLIENT}

${NAME}:	${NAME_SERVER}  ${NAME_CLIENT}
			
all:		${NAME}

clean:
			${RM} ${OBJS}
			
fclean:		clean
			${RM} ${NAME_SERVER}
			${RM} ${NAME_CLIENT}

re:			fclean all
		
