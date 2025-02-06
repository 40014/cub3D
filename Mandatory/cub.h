/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:23:49 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 19:36:54 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define CUB_SIZE 32
# define MINI_MAP_SIZE 2
# define MINI_MAP_SIZE_PLAYER 4
# define SCREEN_SIZE 1600
# define SCREEN_HEIGHT 1000
# define FOV 60
# define P_SPEED 4
# define R_SPEED 2
# define TILE_SIZE 32
# define CELLS_RANGE 6
# define COLOME_SIZE 1
# define DIS_WALL 4
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define O_KEY 32
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESC 65307

typedef struct mlx
{
	void			*mlx_ptr;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_mlx_ptrs;

typedef struct s_texture
{
	void			*img_ptr;
	int				*data;
	int				width;
	int				height;
	int				bpp;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct s_wall_data
{
	double			start_wall;
	double			end_wall;
	double			line_length;
	int				tex_x;
	int				n;
	int				color;
}					t_wall_data;

typedef struct hit
{
	double			hi;
	double			hj;
	double			vj;
	double			vi;
	double			ni;
	int				in_edge;
	double			nj;
	double			lenght;
	int				hit_direction;

}					t_wall_hit;

typedef struct player_info
{
	double			i;
	double			j;
	double			new_i;
	double			new_j;
	int				move_direction;
	int				turn_direction;
	double			rotation_angle;
	double			ray_rotation_angle;
	double			move_speed;
	double			rotation_speed;
	double			real_angle;
	int				fov_lenght;
	int				map_width;
	int				colome;
	int				map_height;
	int				check_one_cub;
	int				color;
	char			**map;
	char			**map2;
	t_wall_hit		*wall_hit;

}					t_player_info;

typedef struct s_keys
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
	int				o;
}					t_keys;

typedef struct s_mini_range
{
	int				start_i;
	int				start_y;
	int				end_i;
	int				end_y;
	double			minimap_p_x;
	double			minimap_p_y;
}					t_mini_range;

typedef struct cub
{
	int				fd;
	char			*readmap;
	char			**map;
	int				map_width;
	int				map_height;
	int				player_x;
	int				player_y;
	char			player_dir;
	int				check_no;
	int				check_we;
	int				check_so;
	int				check_ea;
	int				check_f;
	int				check_c;
	int				tex_x;
	double			wall_x;
	int				n;
	int				mouse_right_pressed;
	int				mouse_left_pressed;
	t_texture		*textures[4];
	char			*path[4];
	int				floor_color;
	int				ceiling_color;
	t_keys			*s_keys;
	t_mlx_ptrs		*mlx_ptrs;
	t_player_info	*player_infos;

}					t_base;

// loading the game
void				initialize_game(t_base *game);

// momazouz part
size_t				ft_strlen2(const char *s);
void				parsing(t_base *game, char *file_name);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_split(const char *s, char c);
void				free_split(char **str);
void				ft_parse_texture(t_base *game, char *tokens);
int					parse_map(t_base *game, int fd);
void				ft_printf_err(char *str);
char				*ft_strdup(const char *s1);
int					parse_color(t_base *game, char *line);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_isdigit_str(char *str);
void				ft_init_struct_game(t_base *game);
int					key_press(int keycode, t_base *game);
int					key_release(int keycode, t_base *game);
void				initialize_keys(t_base *game);
void				my_mlx_pixel_put(t_base *game, int x, int y, int color);
void				draw_minimap(t_base *game);
void				free_texture(char **textur);
void				free_path(t_base *game);
void				cleanup(t_base *game, char *line);
void				error_exit(t_base *game, char *line);
void				error_color(t_base *game, char **rgb, char *str);
void				validate_map(t_base *game);
void				pad_map(t_base *game);
void				initialize_map(t_base *game, char *line);
void				init_weapon_sprite(t_base *game);
int					mouse_press(int button, int x, int y, t_base *game);
int					mouse_release(int button, int x, int y, t_base *game);
void				exit_game(t_base *game);
void				weapon_animation(t_base *game);
void				error_map_close(t_base *game);
void				error_of_door(t_base *game);
int					parse_color_game(t_base *game, char *line);
void				error_texture_exit(t_base *game);

// rendering

double				calculate_wall_x(t_player_info *ray);
int					get_texture_index(t_player_info *player_infos, int n);
int					get_texture_x(t_base *game, double wall_x, int n);
double				get_wall_height(t_player_info *player_infos,
						double distance_projection);
int					out_map(t_player_info *player_infos, int x, int y);

// hdrahm part
void				slide_on_the_wall(t_player_info *player_infos);
void				update_angle(t_player_info *player_infos, int sign,
						double angle);
void				update_new_position(t_player_info *player_infos, int sign,
						double speed, double angle);
double				check_around_pos(t_player_info *player_infos,
						double *len_to_wall);
void				update_position(t_player_info *player_infos, int sign,
						double speed, double angle);
void				get_angle_from_side(t_player_info *player_infos, int d);
void				close_doors(t_player_info *player_infos);
int					check_if_door(t_player_info *player_infos);
int					angle_direction(t_player_info *player_infos);
int					ray_angle_direction(t_player_info *player_infos);
void				apply_values(t_player_info *player_infos, double jsteps,
						double isteps, char c);
void				rendering_3d(t_base *game);
void				get_the_real_hit_point(t_player_info *player_infos);
void				which_element(t_player_info *player_infos);
void				find_inters_up_right_h(t_player_info *player_infos, int y,
						int x);
void				find_inters_up_right_v(t_player_info *player_infos, int y,
						int x);
void				find_inters_up_left_h(t_player_info *player_infos, int y,
						int x);
void				find_inters_up_left_v(t_player_info *player_infos, int y,
						int x);
void				find_inters_down_right_h(t_player_info *player_infos, int y,
						int x);
void				find_inters_down_right_v(t_player_info *player_infos, int y,
						int x);
void				find_inters_down_left_h(t_player_info *player_infos, int y,
						int x);
void				find_inters_down_left_v(t_player_info *player_infos, int y,
						int x);
void				find_inters_right(t_player_info *player_infos);
void				find_inters_left(t_player_info *player_infos);
void				find_inters_up(t_player_info *player_infos);
void				find_inters_down(t_player_info *player_infos);
void				my_mlx_pixel_put2(t_player_info *player_infos, int x, int y,
						int color);
void				find_nearest_wall_hit_down_left(t_player_info *player_infos);
void				find_nearest_wall_hit_up_right(t_player_info *player_infos);
void				find_nearest_wall_hit_down_right(t_player_info *player_infos);
void				find_nearest_wall_hit_up_left(t_player_info *player_infos);
char				get_player_pos_and_dir(t_player_info *player_infos);
int					game_loop(t_base *game);
void				draw_line2(t_base *game, double line_lenght, int color);
void				player_new_pos_up(t_player_info *player_infos);
void				player_new_pos(t_player_info *player_infos);
int					check_the_edge2(t_player_info *player_infos, int j, int i);
double				normalize_angle(double angle);
int					check_the_edge1(t_player_info *player_infos, int j, int i);
void				casting_rays(t_player_info *player_infos);
void				calculate_length(t_player_info *player_infos, double x,
						double y);
void				init_rotation_angle(char d, t_player_info *player_infos);

#endif
