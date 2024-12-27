# ifndef CUB_H
# define CUB_H

# include <math.h>
# include "mlx.h"
//# include "./minilibx/mlx.h"
# include "./get_next_line/get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define CUB_SIZE 32     
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
# endif

#define EPSILON 0.0001
# define FOV 60
# define LINE 20
#define TILE_SIZE 64
#define W_KEY        119
#define S_KEY        115
#define A_KEY        97
#define D_KEY        100
#define LEFT_ARROW   65361
#define RIGHT_ARROW  65363
#define ESC          65307

//# define M_PI 3.14159265358979323846



typedef  struct mlx
{
    void    *mlx_ptr;
    void    *win;
    void    *img;           // Pointer to the image
    char    *addr;          // Address of the image data
    int     bpp;            // Bits per pixel
    int     line_length;    // Number of bytes in a row
    int     endian;  

} t_mlx_ptrs;

typedef struct hit
{
    int hi;
    int hj;
    int vj;
    int vi;
    int ni;
    int nj;
    int lenght;
} t_wall_hit;

typedef struct player_info
{
    float         i;
    float         j;  
    float         new_i;
    float         new_j;
    int         move_direction;
    int         turn_direction;
    float       rotation_angle;
    float       ray_rotation_angle;
    float       move_speed;
    float       rotation_speed;
    int         fov_lenght;
        int     map_width;      
    int     map_height; 
    int         color;
     char    **map;
    t_wall_hit  *wall_hit;

} t_player_info;

typedef struct s_keys
{
    int w;
    int s;
    int a;
    int d;
    int left;
    int right;
} t_keys;

typedef struct cub
{
    int     fd;
    char    *readmap;
    char    **map;
    int     map_width;      
    int     map_height;     
    int     player_x;       
    int     player_y;       
    char    player_dir;     
    char    *textures[4];   
    int     floor_color;    
    int     ceiling_color;
    t_keys  *s_keys;
    t_mlx_ptrs  *mlx_ptrs;
    t_player_info *player_infos;
} t_base;



// momazouz part
size_t  ft_strlen2(const char *s);
void    parsing(t_base *game, char *file_name);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s, char c);
void	free_split(char **str);
// void    ft_parse_texture(t_base *game, char **tokens);
void ft_parse_texture(t_base *game, char *tokens);
int parse_map(t_base *game, int fd);
void    ft_printf_err(char *str);
char	*ft_strdup(const char *s1);
int parse_color(char *line);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_isdigit(int i);
void	*ft_memset(void *dest, int c, size_t count);
void draw_map(t_base *game);
void draw_square(t_base *game, int x, int y, int color);

void ft_init_struct_game(t_base *game);
int key_press(int keycode, t_base *game);
int key_release(int keycode, t_base *game);
void initialize_keys(t_base *game);
void my_mlx_pixel_put(t_base *game, int x, int y, int color);
void draw_square(t_base *game, int x, int y, int color);
void draw_map(t_base *game);




//hdrahm part
void cast_rays(t_base *game);
void which_element(t_player_info *player_infos);
void find_inters_up_right_h(t_player_info *player_infos);
void find_inters_up_right_v(t_player_info *player_infos);
void find_inters_up_left_h(t_player_info *player_infos);
void find_inters_up_left_v(t_player_info *player_infos);
void find_inters_down_right_h(t_player_info *player_infos);
void find_inters_down_right_v(t_player_info *player_infos);
void find_inters_down_left_h(t_player_info *player_infos);
void find_inters_down_left_v(t_player_info *player_infos);
void find_inters_right(t_player_info *player_infos);
void find_inters_left(t_player_info *player_infos);
void find_inters_up(t_player_info *player_infos);
void find_inters_down(t_player_info *player_infos);
void my_mlx_pixel_put2(t_player_info *player_infos ,int x, int y, int color);
void find_nearest_wall_hit_down_left(t_player_info *player_infos);
void find_nearest_wall_hit_up_right(t_player_info *player_infos);
void find_nearest_wall_hit_down_right(t_player_info *player_infos);
void find_nearest_wall_hit_up_left(t_player_info *player_infos);
void get_player_pos(t_player_info *player_infos);
int game_loop(t_base *game);
void player_new_pos_up(t_player_info *player_infos);
void player_new_pos(t_player_info *player_infos);
int check_the_edge2(t_player_info *player_infos, int j, int i);
int check_the_edge1(t_player_info *player_infos, int j, int i);





# endif