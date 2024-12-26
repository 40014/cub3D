#include "../cub.h"


void validate_map(t_base *game)
{
    int     i;
    int     j;
    int     player_found;
    char    c;

    i = 0;
    player_found = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            c = game->map[i][j];
            if (c != '1' && c != ' ' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
            {
                ft_printf_err("Error\nInvalid character in map ");
                printf("Invalid char '%c' at line %d, column %d\n", c, i, j);
                exit(1);
            }
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (player_found)
                {
                    ft_printf_err("Error\nMultiple player positions found\n");
                    exit(1);
                }
                player_found = 1;
                game->player_x = j;
                game->player_y = i;
                game->player_dir = c;
            }
            if (c == '0' || (c == 'N' || c == 'S' || c == 'E' || c == 'W'))
            {
                if (i == 0 || j == 0 || i == game->map_height - 1 || j == game->map_width - 1 || game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ' || game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' ')
                {
                    ft_printf_err("Error\nMap is not closed\n");
                    printf("Map is not closed '%c' at line %d, column %d\n", c, i, j);
                    exit(1);
                }
            }
            j++;
        }
        i++;
    }
    if (!player_found)
    {
        ft_printf_err("Error\nNo player position found\n");
        exit(1);
    }
}

void add_map_line(t_base *game, char *line)
{
    char **new_map;
    int i;
    size_t len;

    len = ft_strlen2(line);
    if (line[0] == '\n' && game->map_height == 0)
        return ;
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    if (game->map == NULL)
    {
        game->map = malloc(sizeof(char *) * 2);
        game->map[0] = ft_strdup(line);
        game->map[1] = NULL;
        game->map_height = 1;
        game->map_width = strlen(line);
        return ;
    }
    new_map = malloc(sizeof(char *) * (game->map_height + 2));
    i = 0;
    while (i < game->map_height)
    {
        new_map[i] = game->map[i];
        i++;
    }
    new_map[i] = ft_strdup(line);
    new_map[i + 1] = NULL;
    free(game->map);
    game->map = new_map;
    game->map_height++;
    if (ft_strlen2(line) > game->map_width)
        game->map_width = ft_strlen2(line);
}

int check_line(t_base *game, char *line)
{
    static int config_lines = 0;
    char    **tokens;

    if (config_lines < 6)
    {
        if (line[0] == '\n' && line[1] == '\0')
            return (0);
        if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 ||
            ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
        {
            //tokens = ft_split(line, ' ');
            ft_parse_texture(game, line);
            //free_split(tokens);
        }
        else if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "C ", 2) == 0))
        {
            if (ft_strncmp(line, "C ", 2) == 0)
                game->ceiling_color = parse_color(ft_strtrim(line + 2, " "));
            else if (ft_strncmp(line, "F ", 2) == 0)
                game->floor_color = parse_color(ft_strtrim(line + 2, " "));
        }
        else
        {
            ft_printf_err("Error\nThe expected type identifier format should be as follows[NO, SO, WE, EA, F, C]\n");
            exit(1);
        }
        config_lines++;
    }
    else
    {
        add_map_line(game, line);
        if (line[0] != '\n')
            printf("%s\n", line);
    }
    return (0);
}

void pad_map(t_base *game)
{
    int i;
    int j;
    size_t len;
    char *new_row;

    i = 0;
    while (i < game->map_height)
    {
        len = ft_strlen2(game->map[i]);
        if (len < game->map_width)
        {
            new_row = malloc(game->map_width + 1);
            j = 0;
            while (j < game->map_width)
            {
                if (j < len)
                    new_row[j] = game->map[i][j];
                else
                    new_row[j] = ' ';
                j++;
            }
            new_row[game->map_width] = '\0';
            free(game->map[i]);
            game->map[i] = new_row;
        }
        i++;
    }
}

int parse_map(t_base *game, int fd)
{
    char *readmap;

    while ((readmap = get_next_line(fd)))
    {
        check_line(game, readmap);
        free(readmap);
    }
    if (game->map == NULL)
    {
        ft_printf_err("Error\nNo map found bro\n");
        exit(1);
    }
    pad_map(game);
    if (game == NULL)
    {
        ft_printf_err("Error\nMap doens't valid\n");
        free_split(game->map);
        exit(1);
    }
    validate_map(game); // Validate the map structure
    return (0);
}
