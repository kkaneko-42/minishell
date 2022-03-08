NAME	:=	minishell
CC		:=	gcc
CFLAGS	:=	-MMD -MP #-fsanitize=address -g
WITH_RL :=	-lreadline
INC_DIR := ./includes
OBJ_DIR	:= ./objs
VPATH	:=	srcs:srcs/utils:srcs/parse:srcs/exec:srcs/exec/builtin
SRCS	:=	main.c \
			signal.c \
			parser.c \
			lexer.c \
			cd.c \
			exec.c \
			do_execve.c \
			echo.c \
			pwd.c \
			env.c \
			export.c \
			export_utils.c \
			export_utils2.c \
			unset.c \
			free_strs.c \
			ft_getenv.c \
			ft_strreplace.c \
			is_snakecase.c \
			addback_envp_list.c \
			get_envp_list.c \
			expand_env.c
OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	:= $(OBJS:.o=.d)
LIBFT_DIR := ./libft
LIBFT := libft.a

$(NAME): set_inputrc $(OBJ_DIR) $(OBJS)
	make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $@ -I $(INC_DIR) $(WITH_RL)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(WITH_RL)

$(OBJ_DIR):
	mkdir -p $@

set_inputrc:
	echo "set echo-control-characters off" >> ~/.inputrc

all: $(NAME)

clean:
	make clean -C $(LIBFT_DIR) 
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re:			fclean all

-include $(DEPS)

.PHONY:     all clean fclean re set_inputrc
