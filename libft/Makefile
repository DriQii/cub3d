CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = libft.a

SRC = ft_atoi.c ft_memchr.c ft_strlcpy.c ft_substr.c get_next_line.c\
	ft_bzero.c ft_memcmp.c ft_strlen.c ft_tolower.c ft_strlcat.c \
	ft_calloc.c ft_memcpy.c ft_strmapi.c ft_strdup.c ft_memccpy.c \
	ft_isalnum.c ft_memmove.c ft_strncmp.c ft_strcpy.c ft_strjoin.c \
	ft_isalpha.c ft_memset.c ft_strncpy.c ft_strcmp.c ft_striteri.c \
	ft_isascii.c ft_putchar_fd.c ft_strnstr.c ft_strchr.c \
	ft_isdigit.c ft_putendl_fd.c ft_strrchr.c ft_strcat.c ft_toupper.c \
	ft_isprint.c ft_putnbr.c ft_strstr.c ft_split.c \
	ft_itoa.c ft_putnbr_fd.c ft_strtrim.c ft_putstr_fd.c \
	ft_print_ex.c ft_printf.c ft_putptr.c utils.c ft_atoll.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)


clean :
	@rm -rf $(OBJ) $(BONUSOBJ)

fclean : clean
	@rm -rf $(NAME)

re : clean all


