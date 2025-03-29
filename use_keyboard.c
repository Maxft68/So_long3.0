/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:43:14 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/29 21:32:56 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	void	collectible_or_not(t_game *game)
{
	int	i;
	int	p_y;
	int	p_x;

	p_y = game->player->instances[0].y;
	p_x = game->player->instances[0].x;
	i = 0;
	if (!game->rainbow || !game->rainbow->instances)
		return ;
	while (i <= game->nb_copy_rainbow)
	{
		if (game->rainbow->instances[i].x == p_x
			&& game->rainbow->instances[i].y == p_y)
		{
			game->map[p_y / P][p_x / P] = '0';
			game->rainbow->instances[i].enabled = false;
			game->rainbow->instances[i].x = -1;
			game->rainbow->instances[i].y = -1;
			game->nb_rainbow--;
		}
		i++;
	}
}

static	void	move_or_not(t_game *game, int y, int x)
{
	int			p_y;
	int			px;
	static int	move = 0;

	p_y = game->player->instances[0].y / P;
	px = game->player->instances[0].x / P;
	if (game->nb_rainbow == 0 && game->map[p_y + y][px + x] == 'E')
	{
		game->player->instances[0].y = game->player->instances[0].y + (y * P);
		game->player->instances[0].x = game->player->instances[0].x + (x * P);
		move++;
		printf("Moves = %d\n", move);
		printf("Congratulations, you saved the unicorn in %dms!!\n",
			(int)(mlx_get_time() * 1000));
		ft_exit_win(game);
	}
	if (game->map[p_y + y][px + x] != '1' && game->map[p_y + y][px + x] != 'E')
	{
		game->player->instances[0].y = game->player->instances[0].y + (y * P);
		game->player->instances[0].x = game->player->instances[0].x + (x * P);
		move++;
		printf("Moves = %d\n", move);
		collectible_or_not(game);
	}
}

void	ft_keyboard(void *param)
{
	t_game			*game;
	static double	last_press_time = 0;
	
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		ft_exit_win(game);
	if (mlx_get_time() - last_press_time >= 0.15)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_W)
			|| mlx_is_key_down(game->mlx,MLX_KEY_S)
			|| mlx_is_key_down(game->mlx, MLX_KEY_A)
			|| mlx_is_key_down(game->mlx, MLX_KEY_D))
			last_press_time = mlx_get_time();
		if (mlx_is_key_down(game->mlx, MLX_KEY_W))
			move_or_not(game, -1, 0);
		if (mlx_is_key_down(game->mlx, MLX_KEY_S))
			move_or_not(game, 1, 0);
		if (mlx_is_key_down(game->mlx, MLX_KEY_A))
			move_or_not(game, 0, -1);
		if (mlx_is_key_down(game->mlx, MLX_KEY_D))
			move_or_not(game, 0, 1);
	}
}
