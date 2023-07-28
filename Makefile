
NAME		= pipex

NAME_BONUS = pipexbonus

FILES	=	main.c util1.c

BONUSFILES =	./bonus/pipex_bonus.c	\
				./bonus/util1_bonus.c	\
				./bonus/get_next_line.c	\

OBJS		=	$(FILES:.c=.o)

OBJS_BONUS	=	$(BONUSFILES:.c=.o)

RM	= rm -f

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

PRINT_PATH	= ./ft_printf --no-print-directory
PRINT_NAME	= ./ft_printf/libftprintf.a

LIBFT_PATH	= ./libft --no-print-directory
LIBFT_NAME	= ./libft/libft.a

all: $(PRINT_NAME) $(LIBFT_NAME) $(NAME)

bonus: $(PRINT_NAME) $(LIBFT_NAME) $(NAME_BONUS)

$(PRINT_NAME):
	@make -C $(PRINT_PATH)

$(LIBFT_NAME):
	@make -C $(LIBFT_PATH)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_NAME) $(PRINT_NAME)

$(NAME_BONUS): $(OBJS_BONUS)
			$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT_NAME) $(PRINT_NAME)

clean:
		@make fclean -C $(PRINT_PATH)
		@make fclean -C $(LIBFT_PATH)
		$(RM) $(OBJS)
		$(RM) $(OBJS_BONUS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(NAME_BONUS)

re:		fclean all