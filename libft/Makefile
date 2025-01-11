NAME = libft.a

FILES = ft_isdigit.c \
		ft_strlen.c \
		ft_memset.c \
		ft_atoi.c \
		ft_calloc.c\
		ft_putstr_fd.c\
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \

CC = cc
C_FLAGS = -Wall -Werror -Wextra

OBJS = $(FILES:.c=.o)

OBJSB = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

bonus : $(OBJSB)
	ar rcs $(NAME) $(OBJSB)

%.o: %.c
	$(CC) -I. $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)
	rm -f libft.so bonus
	rm -f a.out

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(OBJS) $(OBJSB)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(OBJSB)

re: fclean all

.PHONY: all clean fclean re bonus