NAME	:=	a.out
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror -lreadline #-fsanitize=address -g
INC_DIR := ../../includes
VPATH	:=	./:\
			./expansion:\
			./parser:\
			./validate:\
			./lexer:\
			../utils
SRCS	:=	parser.c \
			lexer.c \
			free_strs.c \
			ft_getenv.c \
			ft_strreplace.c \
			is_snakecase.c \
			addback_envp_list.c \
			get_envp_list.c \
			expand_env.c \
			lstdel_head.c \
			lstdel_tail.c \
			lstdel_mid.c \
			re_lexer.c \
			refact_token.c \
			ft_lstjoin.c \
			handle_quotes.c \
			free_content.c \
			is_metachar.c \
			exit_with_error.c \
			check_metachar_target.c \
			check_nb_quotes.c \
			free_cmds.c \
			handle_metachar.c \
			handle_t_cmd.c \
			validate_token.c \
			put_all_tokens.c \
			handle_envname.c
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
