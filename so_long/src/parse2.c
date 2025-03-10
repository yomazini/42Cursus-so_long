/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:15:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 03:13:00 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	ft_counting_cpe(t_game *game, char count)
{
	if (count == 'C')
		game->count_collectable++;
	else if (count == 'E')
		game->count_exit++;
	else if (count == 'P')
		game->count_player++;
}


int is_element_valid(t_game *game)
{
	game->count_collectable = 0;
	game->count_exit = 0;
	game->count_player = 0;
	int i, j;
	i = 0;
	char *allowed_textures = "01PCE";
	while (i < game->num_line)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!ft_strchr(allowed_textures, game->map[i][j]))
				return 0;
			if (game->map[i][j] == 'C' || game->map[i][j] == 'E' || game->map[i][j] == 'P')
				ft_counting_cpe(game ,game->map[i][j]);
			j++;
		}
		i++;
	}
	if (game->count_collectable < 1 || game->count_exit != 1 || game->count_player != 1)
		return 0;
	return 1;
}

void	ft_flood_fill(size_t x, size_t y, size_t num_line, char **map)
{
	if (x < 0 || y < 0 || x > num_line || y > ft_strlen(map[0]))
		return ;
	if (map[x][y] == 'E')
		map[x][y] = '1';
	if (map[x][y] == '1' || map[x][y] == 'V')
		return ;
	map[x][y] = 'V';
	ft_flood_fill(x - 1, y, num_line, map);
	ft_flood_fill(x + 1, y, num_line, map);
	ft_flood_fill(x, y - 1, num_line, map);
	ft_flood_fill(x, y + 1, num_line, map);
}
int		checking_new_map(char **map)
{
	int i, j;
	i = 0;
	char *still_ce = "CE";
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(still_ce,map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return 1;
}

int	validating_new_map(t_game game)
{
	int i, j;
	char **copy_map = ft_split(game.str, '\n');
	if (!copy_map)
		return 0;

	for (i = 0; copy_map[i]; i++)
		for (j = 0; copy_map[i][j]; j++)
			if (copy_map[i][j] == 'P')
			{
				ft_flood_fill(i, j, game.num_line, copy_map);
				if (!checking_new_map(copy_map))
				{
					free_all(copy_map);
					return 0;
				}
			}
	free_all(copy_map);
	return 1;
}
