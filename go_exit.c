/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:22:27 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/30 22:33:07 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return ;
}

static	void	close_all_array(t_game *game)
{
	if (game->map)
		free_array(game->map);
	game->map = NULL;
	if (game->map_to_check)
		free_array(game->map_to_check);
	game->map_to_check = NULL;
}

static	void	delete_texture_image(t_game *game)
{
	if (game->floor)
	mlx_delete_image(game->mlx, game->floor);
	if (game->player)
	mlx_delete_image(game->mlx, game->player);
	if (game->rainbow)
	mlx_delete_image(game->mlx, game->rainbow);
	if (game->unicorn)
	mlx_delete_image(game->mlx, game->unicorn);
	if (game->wall)
	mlx_delete_image(game->mlx, game->wall);
	if (game->t_floor)
		mlx_delete_texture(game->t_floor);
	if (game->t_player)
		mlx_delete_texture(game->t_player);
	if (game->t_rainbow)
		mlx_delete_texture(game->t_rainbow);
	if (game->t_unicorn)
		mlx_delete_texture(game->t_unicorn);
	if (game->t_wall)
		mlx_delete_texture(game->t_wall);
}

void	ft_exit(char *error, t_game *game, mlx_t *mlx)
{
	ft_putstr_fd(error, 1); // remettre 2 a la fin
	close_all_array(game);
	if (game->mlx_init == 1 && mlx)
	{
		delete_texture_image(game);
		mlx_close_window(mlx);
		mlx_terminate(mlx);
	}
	if (game->fd != -1)
		close(game->fd);
	exit(1);
}

void	ft_exit_win(t_game *game)
{
	close_all_array(game);
	mlx_delete_image(game->mlx, game->floor);
	mlx_delete_image(game->mlx, game->player);
	mlx_delete_image(game->mlx, game->rainbow);
	mlx_delete_image(game->mlx, game->unicorn);
	mlx_delete_image(game->mlx, game->wall);
	mlx_delete_texture(game->t_floor);
	mlx_delete_texture(game->t_player);
	mlx_delete_texture(game->t_rainbow);
	mlx_delete_texture(game->t_unicorn);
	mlx_delete_texture(game->t_wall);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	if (game->fd != -1)
		close(game->fd);
	exit(0);
}
