NAME = philo

DIR_OBJ = obj/

DIR_SRC = srcs/

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread -g

#-pthread -fsanitize=thread

RM = rm -f

SRCS = $(wildcard $(DIR_SRC)*.c)

OBJ = $(patsubst $(DIR_SRC)%.c,$(DIR_OBJ)%.o,$(SRCS))

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
		rm -rf $(DIR_OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all 