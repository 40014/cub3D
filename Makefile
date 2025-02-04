NAME = cub3D
BONUS_NAME = cub3D_bonus
CFLAGS = -Wall -Wextra -Werror -w #-fsanitize=address -g3

FLAGS =  -lmlx -lXext -lX11 -lm -lz 

#Mandatory Part
RAY_CASTING	=	Mandatory/ray_casting/find_inters_up_left.c Mandatory/ray_casting/find_inters_down_right.c \
				Mandatory/ray_casting/find_inters_down_left.c Mandatory/ray_casting/find_inters_straight.c  \
				Mandatory/main.c Mandatory/ray_casting/casting_rays.c Mandatory/ray_casting/find_inters_up_right.c \
				Mandatory/movement/moving_player.c Mandatory/movement/movement_utils.c   Mandatory/movement/movement_utils_2.c \
				Mandatory/ray_casting/ray_casting_utils.c Mandatory/movement/check_around_pos.c
			
RENDERING	=	Mandatory/rendering_3d/rendering_3d.c Mandatory/rendering_3d/rendring_utils.c	\

PARSING =	Mandatory/loading_game.c Mandatory/parsing/check_texture_rgb.c Mandatory/parsing/ft_split.c Mandatory/parsing/utils.c    \
				get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c                \
				Mandatory/parsing/intialize_game.c Mandatory/parsing/parsing.c Mandatory/parsing/parsing2.c  Mandatory/parsing/utils_lib.c \
				Mandatory/parsing/utils_parsing.c Mandatory/parsing/validate_map.c Mandatory/parsing/drawing.c  \
				Mandatory/parsing/free_game.c  Mandatory/parsing/handle_keys_mouse.c          \
				Mandatory/parsing/message_errors.c Mandatory/parsing/color_utils.c \
#BOUNUS PART
RAY_CASTING_BONUS	=	bonus/ray_casting/find_inters_up_left.c bonus/ray_casting/find_inters_down_right.c \
				bonus/ray_casting/find_inters_down_left.c bonus/ray_casting/find_inters_straight.c  \
				bonus/main_bonus.c bonus/ray_casting/casting_rays.c bonus/ray_casting/find_inters_up_right.c \
				bonus/movement/moving_player.c bonus/movement/movement_utils.c   bonus/movement/movement_utils_2.c \
				bonus/sprit_animation_bonus.c bonus/ray_casting/ray_casting_utils.c bonus/movement/check_around_pos.c
			
RENDERING_BONUS	=	bonus/rendering_3d/rendering_3d.c bonus/rendering_3d/rendring_utils.c	\

PARSING_BOUNUS =	bonus/loading_game_bonus.c bonus/parsing/check_texture_rgb_bonus.c bonus/parsing/ft_split_bonus.c bonus/parsing/utils_bonus.c    \
				get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c                \
				bonus/parsing/intialize_game_bonus.c bonus/parsing/parsing_bonus.c bonus/parsing/parsing2_bonus.c  bonus/parsing/utils_lib_bonus.c \
				bonus/parsing/minimap_bonus.c bonus/parsing/utils_parsing_bonus.c bonus/parsing/validate_map_bonus.c bonus/parsing/drawing_bonus.c  \
				bonus/parsing/free_game_bonus.c bonus/movement/animation_player_bonus.c bonus/parsing/handle_keys_mouse_bonus.c          \
				bonus/parsing/message_errors_bonus.c bonus/parsing/color_utils_bonus.c \


SOURCES_BONUS  = $(PARSING_BOUNUS) $(RAY_CASTING_BONUS)	$(RENDERING_BONUS)
SOURCES = $(PARSING) $(RAY_CASTING)	$(RENDERING)

#FLAGS = ./minilibx/libmlx.a -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(SOURCES)
	cc $(CFLAGS) $(SOURCES) $(FLAGS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(SOURCES_BONUS)
	cc $(CFLAGS) $(SOURCES_BONUS) $(FLAGS) -o $(BONUS_NAME)

clean :

fclean : clean
	rm -rf $(NAME) $(BONUS_NAME)

re : fclean all
