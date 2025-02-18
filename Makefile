CC = gcc

CFLAGS = -Wall -g -Imlx -Ilibft -Iinclude  -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit

NAME = cub3d

DIR_SRCS	=	./srcs
DIR_OBJS	=	.objs

LST_SRCS =	main.c \
			parsing.c \
			descParsing.c \
			mapParsing.c \
			utils.c \
			initImg.c \
			minimap.c \
			movement.c

LST_OBJS = $(LST_SRCS:.c=.o)

SRCS		=	$(addprefix $(DIR_SRCS)/, $(LST_SRCS))
OBJS		=	$(addprefix $(DIR_OBJS)/, $(LST_OBJS))

ERASE		=	\033[2K\r
BLUE		=	\033[34m
YELLOW		=	\033[33m
GREEN		=	\033[32m
END			=	\033[0m

all : $(NAME)

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	@mkdir -p .objs
	@make -C libft
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(BLUE) > Compilation :$(END) $<\n"


$(NAME) :   $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@printf "$(ERASE)$(GREEN)$(NAME) made !\n$(END)"

clean   :
	@printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	@rm -rdf $(DIR_OBJS)
	@make -C libft clean

fclean  :   clean
	@printf "$(YELLOW)$(NAME) removed$(END)\n"
	@rm -f $(NAME)
	@make -C libft fclean

re      :   fclean all
