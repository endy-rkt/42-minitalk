CLIENT_SRCS = client.c  minitalk_utils_1.c

SERVER_SRCS = server.c minitalk_utils_1.c minitalk_utils_2.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

NAME_CLIENT = client

NAME_SERVER = server

CLIENT_SRCS_BONUS = client_bonus.c minitalk_utils_1.c

SERVER_SRCS_BONUS = server_bonus.c minitalk_utils_1.c minitalk_utils_2.c

CLIENT_OBJS_BONUS = $(CLIENT_SRCS_BONUS:.c=.o)

SERVER_OBJS_BONUS = $(SERVER_SRCS_BONUS:.c=.o)

NAME_CLIENT_BONUS = client_bonus

NAME_SERVER_BONUS = server_bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $<

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all: ${NAME_CLIENT} ${NAME_SERVER}

${NAME_SERVER}: fclean $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o ${NAME_SERVER} $(SERVER_OBJS)

${NAME_CLIENT}: fclean $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o ${NAME_CLIENT} $(CLIENT_OBJS)

bonus: ${NAME_CLIENT_BONUS} ${NAME_SERVER_BONUS}

${NAME_SERVER_BONUS}: fclean $(SERVER_OBJS_BONUS)
	$(CC) $(CFLAGS) -o ${NAME_SERVER_BONUS} $(SERVER_OBJS_BONUS)

${NAME_CLIENT_BONUS}:  fclean $(CLIENT_OBJS_BONUS) 
	$(CC) $(CFLAGS) -o ${NAME_CLIENT_BONUS} $(CLIENT_OBJS_BONUS)

clean:
	${RM} $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_OBJS_BONUS) $(CLIENT_OBJS_BONUS)

fclean: clean
			${RM} ${NAME_SERVER} ${NAME_CLIENT} ${NAME_SERVER_BONUS} ${NAME_CLIENT_BONUS}

re:			fclean all bonus