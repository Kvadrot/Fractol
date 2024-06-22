#Compiler
CC = gcc

CFLAGS = -I ./minilibx-linux
LD_FLAGS = -L ./minilibx-linux -lmlx -lXext -lX11

# Default sources
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Program Name
NAME = fractol

# Default rule
all: $(NAME)

# Make minilibx-linux
minilibx-linux/libmlx.a:
	make -C minilibx-linux

$(NAME): $(OBJS) minilibx-linux/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LD_FLAGS)

# Clean up obj files
clean:
	make -C minilibx-linux clean
	rm -f $(OBJS)

# Full clean up
fclean: fclean
	make -C minilibx-linux fclean
	rm -f $(OBJS)

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re