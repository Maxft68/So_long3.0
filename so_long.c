/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:44:28 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/29 19:56:43 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize(t_game *game, char **argv)
{
	game->map = NULL;
	game->map_to_check = NULL;
	game->name_map = argv[1];
	game->fd = -1;
	game->len = -10;
	game->first_len = -10;
	game->game_line = 1;
	game->nb_rainbow = 0;
	game->nb_copy_rainbow = 0;
	game->nb_players = 0;
	game->nb_unicorn = 0;
	game->pos_x = -1;
	game->pos_y = -1;
	game->mlx_init = -1;
	//game->time = -1;
}

void	initialize_mlx(t_game *game)
{
	game->t_player = NULL;
	game->player = NULL;
	game->t_rainbow = NULL;
	game->rainbow = NULL;
	game->t_floor = NULL;
	game->floor = NULL;
	game->t_wall = NULL;
	game->wall = NULL;
	game->t_unicorn = NULL;
	game->unicorn = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;
	mlx_t	*mlx;

	mlx = NULL;
	if (argc != 2)
		return (1);
	verif_name_map(argv);
	initialize(&game, argv);
	verif_open(&game, argv);
	verif_rectangle(&game);
	fill_the_map(&game, mlx);
	verif_after_fill(&game, mlx);
	begin_mlx(mlx, &game);
}
