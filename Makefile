RESET_COLOR = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
BLUE = \033[94m


NAME = philo

DIR_OBJ = obj/

DIR_SRC = srcs/

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread -g

RM = rm -f

SRCS = $(wildcard $(DIR_SRC)*.c)

OBJ = $(patsubst $(DIR_SRC)%.c,$(DIR_OBJ)%.o,$(SRCS))

$(NAME): $(OBJ)
		@echo "$(BOLD)$(BLUE)Compiling...$(RESET_COLOR)"
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
		@echo "$(BOLD)$(GREEN)Compiling finished$(RESET_COLOR)"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
		@echo "$(BOLD)$(BLUE)Cleaning...$(RESET_COLOR)"
		rm -rf $(DIR_OBJ)

fclean: clean
		$(RM) $(NAME)
		@echo "$(BOLD)$(GREEN)Cleaning finished$(RESET_COLOR)"

re: fclean all 