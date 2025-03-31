/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_and_images.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:52:13 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/31 13:43:06 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(mlx_t *mlx, t_game *game)
{
	game->t_floor = mlx_load_png("./images/floor_75.png");
	game->t_rainbow = mlx_load_png("./images/rainbow_75.png");
	game->t_player = mlx_load_png("./images/player_75.png");
	game->t_wall = mlx_load_png("./images/wall_75.png");
	game->t_unicorn = mlx_load_png("./images/the_door_75.png");
	if (!game->t_floor || !game->t_rainbow || !game->t_player || !game->t_wall
		|| !game->t_unicorn)
		ft_exit("Error\nLoading texture fail\n", game, mlx);
}

void	load_images(mlx_t *mlx, t_game *game)
{
	game->floor = mlx_texture_to_image(mlx, game->t_floor);
	game->player = mlx_texture_to_image(mlx, game->t_player);
	game->rainbow = mlx_texture_to_image(mlx, game->t_rainbow);
	game->wall = mlx_texture_to_image(mlx, game->t_wall);
	game->unicorn = mlx_texture_to_image(mlx, game->t_unicorn);
	if (!game->floor || !game->rainbow || !game->player || !game->wall
		|| !game->unicorn)
		ft_exit("Error\nLoading image fail\n", game, mlx);
}

void	load_to_windows(mlx_t *mlx, t_game *g)
{
	int	y;
	int	x;

	y = -1;
	while (g->map[++y])
	{
		x = -1;
		while (g->map[y][++x] && g->map[y][x] != '\n')
		{
			if (mlx_image_to_window(mlx, g->floor, x * P, y * P) == -1)
				ft_exit("Error mlx_image_floor_to_window\n", g, mlx);
			if (g->map[y][x] == 'C')
				if (mlx_image_to_window(mlx, g->rainbow, x * P, y * P) == -1)
					ft_exit("Error mlx_image_rainbow_to_window\n", g, mlx);
			if (g->map[y][x] == '1')
				if (mlx_image_to_window(mlx, g->wall, x * P, y * P) == -1)
					ft_exit("Error mlx_image_wall_to_window\n", g, mlx);
			if (g->map[y][x] == 'E')
				if (mlx_image_to_window(mlx, g->unicorn, x * P, y * P) == -1)
					ft_exit("Error mlx_image_unicorn_to_window\n", g, mlx);
		}
	}
	if (mlx_image_to_window(mlx, g->player, g->pos_x * P, g->pos_y * P) == -1)
		ft_exit("Error mlx_image_unicorn_to_window\n", g, mlx);
}
