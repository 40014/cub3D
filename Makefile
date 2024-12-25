NAME = cub3D

SOURCE =    main.c parsing.c utils.c ./get_next_line/get_next_line.c \
			./get_next_line/get_next_line_utils.c ft_split.c check_texture_rgb.c \
			parsing2.c utils_lib.c movement.c\
            

CFLAGS = -Wall -Wextra -Werror -w



all: $(NAME)

$(NAME): $(SOURCE)
	cc $(CFLAGS) $(SOURCE) -Lminilibx-linux  -lmlx_Linux -lXext -lX11 -lm -lz  -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all