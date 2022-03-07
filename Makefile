NAME	:=	minishell
CC		:=	gcc
CFLAGS	:=	-lreadline #-fsanitize=address -g
INC_DIR := ./includes
SRCS	:=	./srcs/main.c \
			./srcs/signal.c \
			./srcs/parse/parser.c \
			./srcs/parse/lexer.c \
			./srcs/exec/builtin/cd.c \
			./srcs/exec/exec.c \
			./srcs/exec/do_execve.c \
			./srcs/exec/builtin/echo.c \
			./srcs/exec/builtin/cd.c \
			./srcs/exec/builtin/pwd.c \
			./srcs/exec/builtin/env.c \
			./srcs/exec/builtin/export.c \
			./srcs/exec/builtin/export_utils.c \
			./srcs/exec/builtin/export_utils2.c \
			./srcs/exec/builtin/unset.c \
			./srcs/utils/free_strs.c \
			./srcs/utils/ft_getenv.c \
			./srcs/utils/ft_strreplace.c \
			./srcs/utils/is_snakecase.c \
			./srcs/utils/addback_envp_list.c \
			./srcs/utils/free_strs.c \
			./srcs/utils/get_envp_list.c

OBJS	:= $(SRCS:.c=.o)
LIBFT_DIR := ./libft
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

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re:			fclean all

.PHONY:     all clean fclean re
