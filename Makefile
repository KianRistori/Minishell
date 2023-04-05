NAME = minishell
SRC = main.c cmdtrim.c cmdtrim2.c utils.c free.c parsing.c fill_struct.c execute.c execute2.c execute3.c \
	pwd.c env.c cd.c signal.c echo.c utils2.c fill_t_mini.c remove_char.c print_echo.c
OBJ = $(SRC:.c=.o)

LIBFT = @libft/Makefile
FLAGS = -g -Wall -Wextra -Werror
LIB = libft/libft.a
LINKS = -lreadline

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS) $(OBJ) $(LIB) $(LINKS) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)
	@rm $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     Deleted object files" $(NONE)

$(LIBFT):
	@echo $(CURSIVE)$(GRAY) "     - Compiling Libft ..."
	@make -s -C libft
	@echo $(GREEN)"- Libft ready -"

$(OBJ): $(SRC)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@gcc $(FLAGS) -c $(SRC)

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJ)
	@make -s -C libft clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)
	@make -s -C libft fclean

re: fclean all
