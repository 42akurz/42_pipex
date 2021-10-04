CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar cr
NAME= libft.a
SOURCES = ./ft_pipex.c ./ft_pipex_utils.c 
OBJECTS = $(SOURCES:.c=.o)

#build everything
all: $(NAME)

#make libft
LIB:
	make -C ./libft
	cp ./libft/libft.a $(NAME)

#creates a static library
$(NAME): LIB $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) libft.a -o pipex

#removes all *.o files
clean:
	$(RM) $(OBJECTS)
	make clean -C ./libft

#removes all *.o files + libft.a + libmlx.a
fclean: clean
	$(RM) $(NAME)
	$(RM) ./libft/libft.a
	$(RM) libft.a
	$(RM) pipex

#removes all *.o files + libft.a + libmlx.a and rebuild everything
re: fclean all