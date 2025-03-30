/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:11:57 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/30 18:09:30 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x])
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (map[y][x] == 'E')
	{
		map[y][x] = 'V';
		return ;
	}
	map[y][x] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static	void	verif_all_access(char **map, t_game *game, mlx_t *mlx)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		ft_exit("Error\nMap is NULL", game, mlx);
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'V')
				ft_exit("Error\nInaccessible collectibles or exit\n", game,
					mlx);
			j++;
		}
		i++;
	}
}

void	verif_all_valid_paths(t_game *game, mlx_t *mlx)
{
	flood_fill(game->map_to_check, game->pos_x, game->pos_y);
	verif_all_access(game->map_to_check, game, mlx);
}
