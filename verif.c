/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:50:48 by maxoph            #+#    #+#             */
/*   Updated: 2025/03/31 13:51:07 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	verif_name_map(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nPlease, use a valid extension map\n", 2);
		exit(1);
	}
}

void	verif_open(t_game *game, char **argv)
{
	game->fd = open(argv[1], O_RDONLY);
	if (game->fd == -1)
	{
		ft_putstr_fd("Error\nMap file not found or inaccessible\n", 2);
		exit(1);
	}
}

static void	get_first_len(t_game *game)
{
	char	*line;

	game->fd = open(game->name_map, O_RDONLY);
	if (game->fd == -1)
		ft_exit("Error\nNot possible to open the map\n", game, game->mlx);
	line = get_next_line(game->fd);
	if (!line)
	{
		close(game->fd);
		ft_exit("Error\nGet_next_line failed\n", game, game->mlx);
	}
	game->first_len = ft_strlen(line);
	if (line[game->first_len - 1] == '\n')
		game->first_len--;
	free(line);
}

void	verif_rectangle(t_game *game)
{
	char	*line;

	get_first_len(game);
	line = get_next_line(game->fd);
	while (line)
	{
		if (!line)
		{
			close(game->fd);
			ft_exit("Error\nGet_next_line failed\n", game, game->mlx);
		}
		game->game_line++;
		game->len = ft_strlen(line);
		if (line[game->len - 1] == '\n')
			game->len--;
		if (game->first_len != game->len)
		{
			free(line);
			close(game->fd);
			ft_exit("Error\nPlease, use a rectangle map\n", game, game->mlx);
		}
		free(line);
		line = get_next_line(game->fd);
	}
	close(game->fd);
}
