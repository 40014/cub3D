NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -w

FLAGS =  -lmlx -lXext -lX11 -lm -lz 

RAY_CASTING =	ray_casting/find_inters_up_left.c ray_casting/find_inters_down_right.c \
				ray_casting/find_inters_down_left.c ray_casting/find_inters_straight.c  \
				main.c ray_casting/ray_hitting_wall.c ray_casting/find_inters_up_right.c \
				movement/moving_player.c
			
			
PARSING =	parsing/check_texture_rgb.c parsing/ft_split.c parsing/utils.c                   \
			get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c                \
			parsing/intialize_game.c parsing/parsing.c parsing/parsing2.c  parsing/utils_lib.c \

SOURCES = $(PARSING) $(RAY_CASTING)	


#FLAGS = ./minilibx/libmlx.a -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(SOURCES)
	cc $(CFLAGS) $(SOURCES) $(FLAGS) -o $(NAME)

clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all
