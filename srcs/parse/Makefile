NAME	:=	a.out
CC		:=	gcc
CFLAGS	:=	-lreadline #-fsanitize=address -g
INC_DIR := ../../includes
SRCS	:=	./parser.c ./lexer.c \
			./re_lexer.c ./refact_token.c \
			./expand_env.c ../utils/lstdel_head.c \
			../utils/lstdel_tail.c ../utils/lstdel_mid.c \
			../utils/ft_lstjoin.c ../utils/ft_getenv.c \
			../utils/ft_strreplace.c ../utils/is_snakecase.c \
			../utils/get_envp_list.c ../utils/free_strs.c \
			../utils/addback_envp_list.c ./handle_quotes.c \
			../utils/free_content.c ../utils/exit_with_error.c \
			../utils/is_metachar.c
OBJS	:= $(SRCS:.c=.o)
LIBFT_DIR := ../../libft
LIBFT := libft.a

$(NAME):	$(OBJS)
	make bonus -C $(LIBFT_DIR)
	$(CC) -I $(INC_DIR) $^ $(LIBFT_DIR)/$(LIBFT) -o $@ $(CFLAGS)

.c.o:
	$(CC) -I $(INC_DIR) -c $^ -o $@ $(CFLAGS)

all:	$(NAME)

clean:
	make clean -C $(LIBFT_DIR) 
	rm -f $(OBJS)
	rm -f *.txt

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re:			fclean all

.PHONY:     all clean fclean re
