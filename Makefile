CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = minishell
SRC_DIR = . ./libft ./builtin ./parsing
SRC = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJ = $(SRC:.c=.o)
DEPS = minishell.h
RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

READLINE = $(shell brew --prefix readline)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "${GREEN}Creating executable...${NC}"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(READLINE)/lib -lreadline
	@echo "${GREEN}Executable $(NAME) created.${NC}"

%.o: %.c $(DEPS)
	@echo "${GREEN}Compiling $<...${NC}"
	@$(CC) $(CFLAGS) -I$(READLINE)/include -c $< -o $@

clean:
	@echo "${RED}Cleaning object files...${NC}"
	@rm -f $(OBJ)

fclean: clean
	@echo "${RED}Cleaning executable...${NC}"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re