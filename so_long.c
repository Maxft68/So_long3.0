/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:44:28 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/27 15:01:14 by maxoph           ###   ########.fr       */
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
	close(game.fd);
	fill_the_map(&game, mlx);
	verif_after_fill(&game, mlx);
	begin_mlx(mlx, &game);
	close_all_array(&game);
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

void	load_textures(mlx_t *mlx, t_game *game)
{
	game->t_floor = mlx_load_png("./floor_small.png");
	game->t_rainbow = mlx_load_png("./rainbow_small.png");
	game->t_player = mlx_load_png("./player_small.png");
	game->t_wall = mlx_load_png("./wall_small.png");
	game->t_unicorn = mlx_load_png("./the_door_small.png");
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

void	begin_mlx(mlx_t *mlx, t_game *game)
{
	if (!(mlx = mlx_init(P * game->first_len, P * game->game_line, "so_long",
				true)))
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

void	move_or_not(t_game *game, int y, int x)
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
		printf("Congratulations, you saved the unicorn !!\n");
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
	return ;
}

void	collectible_or_not(t_game *game)
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

void	ft_hook(void *param)
{
	t_game			*game;
	static double	last_press_time = 0;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
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

void	verif_after_fill(t_game *game, mlx_t *mlx)
{
	verif_p_c_e(game, mlx);
	verif_nb_p_c_e(game, mlx);
	verif_map_close(game, mlx);
	verif_all_valid_paths(game, mlx);
}

void	verif_all_access(char **map, t_game *game, mlx_t *mlx)
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

void	flood_fill(char **map, int x, int y)
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

void	verif_all_valid_paths(t_game *game, mlx_t *mlx)
{
	flood_fill(game->map_to_check, game->pos_x, game->pos_y);
	verif_all_access(game->map_to_check, game, mlx);
}

void	verif_map_close(t_game *game, mlx_t *mlx)
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

int	is_p_c_e(char c, t_game *game, mlx_t *mlx)
{
	if (c == 'P' || c == 'C' || c == 'E' || c == '1' || c == '0' || c == '\n')
		return (1);
	else
	{
		ft_exit("Error\nInvalid character detected in the map\n", game, mlx);
		return (-1);
	}
}

void	verif_nb_p_c_e(t_game *game, mlx_t *mlx)
{
	if (game->nb_players != 1 || game->nb_rainbow <= 0 || game->nb_unicorn != 1)
	{
		if (game->nb_players != 1)
			ft_putstr_fd("Error\nThe map need 1 player, no more no less\n", 1);
		// fd a remettre a la fin
		if (game->nb_unicorn != 1)
			ft_putstr_fd("Error\nThe map need 1 exit, no more no less\n", 1);
		// fd a remettre a la fin
		if (game->nb_rainbow <= 0)
			ft_putstr_fd("Error\nThe map need at least, 1 collectible\n", 1);
		// fd a remettre a la fin
		ft_exit("", game, mlx);
	}
}

void	verif_p_c_e(t_game *game, mlx_t *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i, game->map[i])
	{
		j = -1;
		while (++j, game->map[i][j])
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
				{
					game->nb_rainbow++;
					game->nb_copy_rainbow++;
				}
				else if (game->map[i][j] == 'E')
					game->nb_unicorn++;
			}
		}
	}
}
void	delete_texture_image(t_game *game)
{
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
}

void	ft_exit(char *error, t_game *game, mlx_t *mlx)
{
	ft_putstr_fd(error, 1); // remettre 2 a la fin
	close_all_array(game);
	delete_texture_image(game);
	if (game->mlx_init == 1)
	{
		mlx_close_window(mlx);
		mlx_terminate(mlx);
	}
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
	exit(0);
}

void	verif_name_map(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nPlease, use a valid extension map\n", 1);
		// remettre sur 2 a la fin
		exit(1);
	}
}

void	verif_open(t_game *game, char **argv)
{
	game->fd = open(argv[1], O_RDONLY);
	if (game->fd == -1)
	{
		ft_putstr_fd("Error\nMap file not found or inaccessible\n", 1);
		// remettre sur 2 a la fin
		exit(1);
	}
}

void	close_all_array(t_game *game)
{
	if (game->map)
		free_array(game->map);
	game->map = NULL;
	if (game->map_to_check)
		free_array(game->map_to_check);
	game->map_to_check = NULL;
}

void	free_array(char **array)
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

void	verif_rectangle(t_game *game)
{
	char	*line;

	game->fd = open(game->name_map, O_RDONLY);
	if (game->fd == -1)
		ft_exit("Error\nNot possible to open the map\n", game, game->mlx);
	line = get_next_line(game->fd);
	if(!line)
		ft_exit("Error\nGet_next_line failed\n", game, game->mlx);
	game->first_len = ft_strlen(line);
	if (line[game->first_len - 1] == '\n')
		game->first_len--;
	free(line);
	while ((line = get_next_line(game->fd)))
	{
		if (!line)
			ft_exit("Error\nGet_next_line failed\n", game, game->mlx);
		game->game_line++;
		game->len = ft_strlen(line);
		if (line[game->len - 1] == '\n')
			game->len--;
		if (game->first_len != game->len)
		{
			ft_exit("Error\nPlease, use a rectangle map\n", game, game->mlx);
			free(line);
		}
		free(line);
	}
}

void	print_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
}

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
