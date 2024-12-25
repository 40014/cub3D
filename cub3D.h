#ifndef cub3D_H
# define cub3D_H

# include "./get_next_line/get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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

    void    *mlx;           
    void    *win;          
    void    *img;           
    char    *addr;          
    int     bpp;           
    int     line_length;    
    int     endian;
    t_keys  *s_keys;
} t_base;

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
int game_loop(t_base *game);
void draw_map(t_base *game);
void draw_square(t_base *game, int x, int y, int color);

#endif