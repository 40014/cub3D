# include "cub.h"



int main(int ac, char **av)
{
    t_base game;

    if (ac != 2)
        return (1);
    ft_init_struct_game(&game);
    parsing(&game, av[1]);
    initialize_game(&game);
    return(0);
}