#include "cub3D.h"
#include <string.h>
int ft_isdigit_str(char *str)
{
    int i;

    if (!str || !*str)
        return (0);
    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void    check_commas(char *line)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == ',')
            j++;
        i++;
    }
    if (j > 2)
    {
        printf("Error\nIvalid color format, more than two commas\n");
        exit(1);
    }
}

void    print_token(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        printf("this is token[%d] = '%s'\n", i, tokens[i]);
        i++;
    }
}

void    check_texture_file(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        ft_printf_err("Error\nTexture file doesn't exist\n");
        free(file);
        exit(1);
    }
}

void ft_parse_texture(t_base *game, char *tokens)
{
    int     index;
    char    *path;
    char    **split;

    path = NULL;
    path = ft_strtrim(tokens + 3, " \t\n");
    // printf("path = '%s'\n", path);
    check_texture_file(path);
    split = ft_split(tokens, ' ');
    // print_token(split);
    if (ft_strncmp(split[0], "NO", 3) == 0)
        index = 0;
    else if (ft_strncmp(split[0], "SO", 3) == 0)
        index = 1;
    else if (ft_strncmp(split[0], "WE", 3) == 0)
        index = 2;
    else if (ft_strncmp(split[0], "EA", 3) == 0)
        index = 3;
    else
    {
        ft_printf_err("Error\nInvalid texture identifier. Must be NO, SO, WE, or EA\n");
        exit(1);
    }
    if (ft_strlen2(path) == 0)
    {
        printf("Error\nInvalid texture path. The path cannot be empty.\n");
        free(path);
        exit(1);
    }
    game->textures[index] = ft_strdup(path);
    if (path != NULL)
        free(path);
    free_split(split);
        
}

int parse_color(char *line)
{
    char *trimmed_line;
    char **rgb;
    int color;
    char *trimmed_rgb;
    int i;

    i = 0;
    trimmed_line = ft_strtrim(line, " \n");
    check_commas(trimmed_line);
    rgb = ft_split(trimmed_line, ',');
    free(trimmed_line);
    if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL) // Check if exactly three components are present
    {
        ft_printf_err("Error\nInvalid color format: requires exactly 3 values separated by commas.\n");
        free_split(rgb);
        exit(1);
    }
    while (i < 3)
    {
        trimmed_rgb = ft_strtrim(rgb[i], " ");
        free(rgb[i]);
        rgb[i] = trimmed_rgb;
        if (!ft_isdigit_str(rgb[i]))
        {
            ft_printf_err("Error\nColor values must be numeric\n");
            free_split(rgb);
            exit(1);
        }
        i++;
    }
    color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
    if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 ||
        ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255 ||
        ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
    {
        ft_printf_err("Error\nColor values must be between 0 and 255.\n");
        free_split(rgb);
        exit(1);
    }
    free_split(rgb);
    return (color);
}
