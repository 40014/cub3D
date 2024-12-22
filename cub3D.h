#ifndef cub3D_H
# define cub3D_H

# include "./get_next_line/get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// typedef struct cub
// {
//     int     fd;
//     char	*readmap;
//     char    **map;
    
// }   t_base;

typedef struct cub
{
    int     fd;
    char    *readmap;
    char    **map;
    int     map_width;      // Map width
    int     map_height;     // Map height
    int     player_x;       // Player x position
    int     player_y;       // Player y position
    char    player_dir;     // Player direction (N, S, E, W)
    char    *textures[4];   // NO, SO, WE, EA
    int     floor_color;    // RGB value packed into an integer
    int     ceiling_color;  // RGB value packed into an integer

    void    *mlx;           // Pointer to the MiniLibX connection
    void    *win;           // Pointer to the MiniLibX window
    void    *img;           // Pointer to the image
    char    *addr;          // Address of the image data
    int     bpp;            // Bits per pixel
    int     line_length;    // Number of bytes in a row
    int     endian;         // Endian type
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

#endif