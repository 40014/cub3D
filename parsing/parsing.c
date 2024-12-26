#include "../cub.h"

void    ft_printf_err(char *str)
{
    size_t i;

    i = ft_strlen2(str);
    write(2, str, i);
}

void printf_error(char *str, char c, int i, int j)
{
    
}

int    check_path(char *name)
{
    size_t      i;
    int     j;
    int     r;

    i = ft_strlen2(name);
    j = 4;
    r = 0;
    while (j > 0 && i > 0)
    {
        if (name[i - 1] == ".cub"[j - 1])
		{
			r++;
			j--;
			i--;
		}
		else
			break ;
    }
    if (!(r == 4 && j == 0))
    {
        ft_printf_err("Error\n the file name of map doesn't valide\n");
        return (1);
    }
    return (0);
}

void    parsing(t_base *game, char *file_name)
{
    int fd;

    if (check_path(file_name) == 1)
        exit(1);
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        ft_printf_err("Error\n the file doesn't exist\n");
        exit(1);
    }
    parse_map(game, fd);
}
