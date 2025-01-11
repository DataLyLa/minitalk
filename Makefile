NAME_SERVER = server
NAME_CLIENT = client
LIBFT = libft
LIBFT_A = $(LIBFT)/libft_a
FT_PRINTF = ft_printf
LIBFT_PRINTF_A = $(FT_PRINTF)/libftprintf_a

CC = cc
C_FLAGS = -Wall -Werror -Wextra -I $(LIBFT) -I $(FT_PRINTF)

SERVER = server.c
CLIENT = client.c
FILES = hand_error.c

O_SERVER = $(SERVER:.c=.o)
O_CLIENT = $(CLIENT:.c=.o)
O_FILES = $(FILES:.c=.o)

BLUE = \033[0;34m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = ✔
VALID = $(GREEN)✔
ERROR = $(RED)✘
PROJECT = $(BLUE)Minitalk Project$(RESET)


all:
	@echo "	$(CHECK) $(PROJECT) Building in progress... "
	@$(MAKE) -s $(LIBFT_A) $(LIBFT_PRINTF_A) $(NAME_SERVER) $(NAME_CLIENT)
	@echo "\n  	$(BLUE)___	__ _Minitalk Project Build_ __	___$(RESET)\n"

$(LIBFT_A) :
	@$(MAKE) -C $(LIBFT) >/dev/null && \
	echo "		x Libft [ $(VALID)$(RESET) ]" || echo "		x Libft [ $(ERROR)$(RESET) ]"

$(LIBFT_PRINTF_A) :
	@$(MAKE) -C $(FT_PRINTF) >/dev/null && \
	echo "		x Ft_Printf [ $(VALID)$(RESET) ]" || echo "		x Ft_Printf [ $(ERROR)$(RESET) ]"

$(NAME_SERVER) : $(O_SERVER) $(O_FILES)
	@$(CC) $(C_FLAGS) -o $(NAME_SERVER) $(O_SERVER) $(O_FILES) -L $(LIBFT) -lft -L $(FT_PRINTF) -lftprintf && \
	echo "		x SERVER [ $(GREEN)Ready$(RESET) ]" || echo "		x SERVER [ $(RED)Error$(RESET) ]"

$(NAME_CLIENT) : $(O_CLIENT) $(O_FILES)
	@$(CC) $(C_FLAGS) -o $(NAME_CLIENT) $(O_CLIENT) $(O_FILES) -L$(LIBFT) -lft -L$(FT_PRINTF) -lftprintf && \
	echo "		x CLIENT [ $(GREEN)Ready$(RESET) ]" || echo "		x CLIENT [ $(RED)Error$(RESET) ]"

%.o: %.c
	@$(CC) $(C_FLAGS) -c $< -o $@ && \
	echo "		  files complilation [ $(VALID)$(RESET) ]" || echo "		  files complilation [ $(RED) failed$(RESET) ]"

clean :
	@echo "	$(CHECK)Start Cleaning ..."
	@$(MAKE) clean -C $(LIBFT) >/dev/null 2>&1
	@$(MAKE) clean -C $(FT_PRINTF) >/dev/null 2>&1
	@rm -f $(O_SERVER) $(O_CLIENT) $(O_FILES) >/dev/null 2>&1
	@echo "		x Cleaning [ $(VALID) complete$(RESET) ]" || echo "		x Cleaning [ $(ERROR) failed$(RESET) ]" 
	@echo "	$(CHECK) $(PROJECT) Clean ..."


fclean : 
	@echo "	$(CHECK) Start Full Cleaning ..."
	@$(MAKE) clean >/dev/null 2>&1
	@$(MAKE) fclean -C $(LIBFT) >/dev/null 2>&1
	@$(MAKE) fclean -C $(FT_PRINTF) >/dev/null 2>&1
	@rm -f $(NAME_SERVER) $(NAME_CLIENT) $(O_FILES)>/dev/null 2>&1
	@echo "		x Full Cleaning [ $(VALID) complete$(RESET) ]" || echo "		x Full Cleaning [ $(ERROR) failed$(RESET) ]" 
	@echo "	$(CHECK) $(PROJECT) Completelly Clean ..."

re: 
	@echo "	$(CHECK) $(PROJECT) Rebuilt in progress ..."
	@$(MAKE) -s fclean all 
	
.PHONY: all clean fclean re