SRCS_DIR	= ./srcs

OBJS_DIR	= ./objs

SRCS		= fdf.c

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

NAME		= fdf

CC			= clang-9 

CFLAGS		= -Wall -Werror -Wextra -O3 -g -fsanitize=address

RM	= rm -rf

MLX_DIR	= minilibx-linux

all:		mlx $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -I./$(MLX_DIR) -lbsd -lm -lX11 -lXext -L ./$(MLX_DIR) -lmlx -o $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

mlx:		
			$(MAKE) -C $(MLX_DIR)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			cd $(MLX_DIR) && make clean

re:			fclean all

.PHONY:		all clean fclean re mlx
