/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:32:54 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/29 19:33:19 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_the_map(t_game *game, mlx_t *mlx)
{
	char	*map;
	int		i;

	game->fd = open(game->name_map, O_RDONLY);
	if (game->fd == -1)
		ft_exit("Error\nNot possible to open the map\n", game, mlx);
	game->map = malloc(sizeof(char *) * (game->game_line + 1));
	game->map_to_check = malloc(sizeof(char *) * (game->game_line + 1));
	if (!game->map_to_check || !game->map)
		ft_exit("Error\nMalloc failure\n", game, mlx);
	i = 0;
	map = get_next_line(game->fd);
	if (!map)
		ft_exit("Error get_next_line", game, mlx);
	while (map)
	{
		game->map[i] = ft_strdup(map);
		game->map_to_check[i] = ft_strdup(map);
		if (!game->map[i] || !game->map_to_check[i++])
			ft_exit("Error\nStrdup failure\n", game, mlx);
		free(map);
		map = get_next_line(game->fd);
	}
	game->map[i] = NULL;
	game->map_to_check[i] = NULL;
}
