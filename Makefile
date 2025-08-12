NAME    := philo
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g

SRC     := assign_forks.c data_init.c dinner.c get_set.c main.c monitor.c parsing.c single_philo.c synchronization.c time.c utils.c write_clean.c
OBJ     := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -pthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
