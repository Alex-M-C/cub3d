# Executable name
NAME		= cub3D

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes -I$(MINILIBXDIR)

# Sources (Add your specific files here)
SRCS		= src/main.c				\
			  src/map_extraction.c		\
			  src/map_validation.c		\
			  src/file_parser.c			\
			  src/set_visuals.c			\
			  src/cub3d_utils.c			\
			  src/debug.c				\
			  src/window.c				\
			  src/events.c				\
			  src/player_move.c			\
			  src/raycast.c				\
			  src/render.c				\
			  src/render3d.c

OBJS		= $(SRCS:.c=.o)

# Directories
LIBDIR		= libft/
LIBFT		= $(LIBDIR)/libft.a
MINILIBXDIR	= minilibx-linux
MINILIBX	= $(MINILIBXDIR)/libmlx.a

# Default rule
all: $(NAME)

# Linking the executable
$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBDIR) -lft -L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm

# Build libraries
$(LIBFT):
	$(MAKE) -C $(LIBDIR) all

$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR) all

# Compile objects
%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean objects
clean:
	$(MAKE) -C $(LIBDIR) clean
	rm -f $(OBJS)

# Clean executable and objects
fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re