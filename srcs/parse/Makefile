NAME	:=	a.out
CC		:=	gcc
CFLAGS	:=	-lreadline #-fsanitize=address -g
INC_DIR := ../../includes
SRCS	:=	./parser.c ./lexer.c
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

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re:			fclean all

.PHONY:     all clean fclean re
