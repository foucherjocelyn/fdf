SRCS_DIR	= ./srcs

OBJS_DIR	= ./objs

SRCS		= fdf.c draw_line.c file_to_lst.c parse_map.c cart_to_iso.c draw_map.c

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

NAME		= fdf

CC			= clang-9 

CFLAGS		= -Wall -Werror -Wextra -O3 -g -fsanitize=address

RM			= rm -rf

MLX_DIR		= minilibx-linux

LIBFT_DIR	= libft

INCLUDES	= -I ./includes -I ./libft

all:		libft mlx $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT_DIR)/libft.a -I./$(MLX_DIR) -lbsd -lm -lX11 -lXext -L ./$(MLX_DIR) -lmlx -o $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

mlx:		
			$(MAKE) -C $(MLX_DIR)

libft:
			$(MAKE) -C $(LIBFT_DIR)

clean:
			$(RM) $(OBJS)
			cd $(MLX_DIR) && make clean
			cd $(LIBFT_DIR) && make clean

fclean:		clean
			$(RM) $(NAME)
			cd $(MLX_DIR) && make clean
			cd $(LIBFT_DIR) && make fclean

re:			fclean all

.PHONY:		all clean fclean re mlx libft
