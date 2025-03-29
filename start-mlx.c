/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:23:58 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/29 18:27:00 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	begin_mlx(mlx_t *mlx, t_game *game)
{
	mlx = mlx_init(P * game->first_len, P * game->game_line, "so_long", true);
	if (!mlx)
		ft_exit("Error\nMlx_init fail\n", game, mlx);
	game->mlx_init = 1;
	game->mlx = mlx;
	initialize_mlx(game);
	load_textures(mlx, game);
	load_images(mlx, game);
	load_to_windows(mlx, game);
	mlx_loop_hook(game->mlx, &ft_hook, game);
	mlx_loop(mlx);
}
