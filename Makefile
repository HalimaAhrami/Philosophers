NAME = philo

SRCS = philo.c utils.c life.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS =-Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  -lpthread 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
