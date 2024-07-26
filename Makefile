# Compiler
CC = gcc

# Compiler and linker flags
CFLAGS = -I ./minilibx-linux
LD_FLAGS = -L ./minilibx-linux -lmlx -lXext -lX11 -lm

# Source and object files
SRCS = main.c common_utilities.c mandelbrot_fts.c julia_fts.c ft_atod.c main_obj_init_ft.c
OBJS = $(SRCS:.c=.o)

# Program name
NAME = fractol

# MiniLibX library
MINILIB = ./minilibx-linux/libmlx.a

# Default rule
all: $(MINILIB) $(NAME)

# Build the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LD_FLAGS)

# Build MiniLibX
$(MINILIB):
	make -C minilibx-linux

# Clean object files
clean:
	make -C minilibx-linux clean
	rm -f $(OBJS)

# Full clean
fclean: clean
	make -C minilibx-linux fclean
	rm -f $(NAME)

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', and 're' are not interpreted as file names
.PHONY: all clean fclean re