/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_after_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:53:39 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/31 13:08:35 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_p_c_e(char c, t_game *game, mlx_t *mlx)
{
	if (c == 'P' || c == 'C' || c == 'E' || c == '1' || c == '0' || c == '\n')
		return (1);
	else
	{
		ft_exit("Error\nInvalid character detected in the map\n", game, mlx);
		return (-1);
	}
}

static void	verif_p_c_e(t_game *game, mlx_t *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (is_p_c_e(game->map[i][j], game, mlx) == 1)
			{
				if (game->map[i][j] == 'P')
				{
					game->nb_players++;
					game->pos_x = j;
					game->pos_y = i;
				}
				else if (game->map[i][j] == 'C')
					game->nb_rainbow++;
				else if (game->map[i][j] == 'E')
					game->nb_unicorn++;
			}
		}
	}
}

static void	verif_nb_p_c_e(t_game *game, mlx_t *mlx)
{
	if (game->nb_players != 1 || game->nb_rainbow <= 0 || game->nb_unicorn != 1)
	{
		if (game->nb_players != 1)
			ft_putstr_fd("Error\nThe map need 1 player, no more no less\n", 2);
		if (game->nb_unicorn != 1)
			ft_putstr_fd("Error\nThe map need 1 exit, no more no less\n", 2);
		if (game->nb_rainbow <= 0)
			ft_putstr_fd("Error\nThe map need at least, 1 collectible\n", 2);
		ft_exit("", game, mlx);
	}
}

static void	verif_map_close(t_game *game, mlx_t *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i] && i < game->game_line)
	{
		j = 0;
		while (game->map[i][j] && j < game->first_len)
		{
			if ((i == 0 || i == (game->game_line - 1))
				&& game->map[i][j] != '1')
				ft_exit("Error\nNo wall around the map\n", game, mlx);
			else if ((j == 0 || j == (game->first_len - 1))
				&& game->map[i][j] != '1')
				ft_exit("Error\nNo wall around the map\n", game, mlx);
			j++;
		}
		i++;
	}
}

void	verif_after_fill(t_game *game, mlx_t *mlx)
{
	verif_p_c_e(game, mlx);
	game->nb_copy_rainbow = game->nb_rainbow;
	verif_nb_p_c_e(game, mlx);
	verif_map_close(game, mlx);
	verif_all_valid_paths(game, mlx);
}
