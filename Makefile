NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -w #-fsanitize=address -g3

FLAGS =  -lmlx -lXext -lX11 -lm -lz 

RAY_CASTING	=	bonus/ray_casting/find_inters_up_left.c bonus/ray_casting/find_inters_down_right.c \
				bonus/ray_casting/find_inters_down_left.c bonus/ray_casting/find_inters_straight.c  \
				bonus/main.c bonus/ray_casting/casting_rays.c bonus/ray_casting/find_inters_up_right.c \
				bonus/movement/moving_player.c bonus/movement/movement_utils.c   bonus/movement/movement_utils_2.c \
				bonus/sprit_animation.c bonus/ray_casting/ray_casting_utils.c bonus/movement/check_around_pos.c
			
RENDERING	=	bonus/rendering_3d/rendering_3d.c bonus/rendering_3d/rendring_utils.c	\

PARSING		=	bonus/loading_game.c bonus/parsing/check_texture_rgb.c bonus/parsing/ft_split.c bonus/parsing/utils.c    \
				get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c                \
				bonus/parsing/intialize_game.c bonus/parsing/parsing.c bonus/parsing/parsing2.c  bonus/parsing/utils_lib.c \
				bonus/parsing/minimap.c bonus/parsing/utils_parsing.c bonus/parsing/validate_map.c bonus/parsing/drawing.c  \
				bonus/parsing/free_game.c bonus/movement/animation_player.c bonus/parsing/handle_keys_mouse.c          \
				bonus/parsing/message_errors.c bonus/parsing/color_utils.c \

SOURCES = $(PARSING) $(RAY_CASTING)	$(RENDERING)


#FLAGS = ./minilibx/libmlx.a -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(SOURCES)
	cc $(CFLAGS) $(SOURCES) $(FLAGS) -o $(NAME)

clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all
