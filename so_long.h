/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:46:41 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/30 19:23:16 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft/libft.h"
# include "./libft/printf/ft_printf.h"
# include "./libft/gnl/get_next_line.h"
# include "MLX42/MLX42.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# define P 75

typedef struct s_game
{
	char			**map;
	char			**map_to_check;
	int				fd;
	char			*name_map;
	int				len;
	int				first_len;
	int				game_line;
	int				pos_x;
	int				pos_y;
	int				nb_rainbow;
	int				nb_copy_rainbow;
	int				nb_players;
	int				nb_unicorn;
	int				mlx_init;
	mlx_texture_t	*t_player;
	mlx_image_t		*player;
	mlx_texture_t	*t_rainbow;
	mlx_image_t		*rainbow;
	mlx_texture_t	*t_floor;
	mlx_image_t		*floor;
	mlx_texture_t	*t_wall;
	mlx_image_t		*wall;
	mlx_texture_t	*t_unicorn;
	mlx_image_t		*unicorn;
	mlx_t			*mlx;
}			t_game;

void			initialize(t_game *game, char **argv);
void			verif_name_map(char **argv);
void			verif_open(t_game *game, char **argv);
void			verif_rectangle(t_game *game);
void			fill_the_map(t_game *game, mlx_t *mlx);
void			ft_exit(char *error, t_game *game, mlx_t *mlx);
void			ft_exit_win(t_game *game);
void			verif_all_valid_paths(t_game *game, mlx_t *mlx);
void			verif_after_fill(t_game *game, mlx_t *mlx);
void			begin_mlx(mlx_t *mlx, t_game *game);
void			load_textures(mlx_t *mlx, t_game *game);
void			initialize_mlx(t_game *game);
void			load_images(mlx_t *mlx, t_game *game);
void			load_to_windows(mlx_t *mlx, t_game *game);
void			ft_keyboard(void *game);

#endif