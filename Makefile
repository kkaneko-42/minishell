NAME	:=	minishell
CC		:=	gcc
CFLAGS	:=	#-fsanitize=address -g
INC_DIR := ./includes
SRCS	:=	main.c
SRC_DIR := ./srcs
OBJ_DIR := ./objs
OBJS	:= $(SRCS:.c=.o)
LIBFT_DIR := ./libft
LIBFT := libft.a

all:	$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(NAME):	$(addprefix $(OBJ_DIR)/, $(OBJS))
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT) $^ -I $(INC_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c	
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $^ -o $@

clean:
	make clean -C $(LIBFT_DIR) 
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re:			fclean all

.PHONY:     all clean fclean re
