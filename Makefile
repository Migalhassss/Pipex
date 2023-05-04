
NAME		= pipex

FILES	=	main.c util1.c

OBJS		=	$(FILES:.c=.o)

RM	= rm -f

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

PRINT_PATH	= ./ft_printf --no-print-directory
PRINT_NAME	= ./ft_printf/libftprintf.a

LIBFT_PATH	= ./libft --no-print-directory
LIBFT_NAME	= ./libft/libft.a

all: $(PRINT_NAME) $(LIBFT_NAME) $(NAME)

$(PRINT_NAME):
	@make -C $(PRINT_PATH)

$(LIBFT_NAME):
	@make -C $(LIBFT_PATH)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_NAME) $(PRINT_NAME)

clean:
		@make fclean -C $(PRINT_PATH)
		@make fclean -C $(LIBFT_PATH)
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all