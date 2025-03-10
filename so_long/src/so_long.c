/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 01:46:47 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_all(char **map)
{
	int i;

	i = 0;
	if (!map)
		return ;
	while(map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	handle_error(t_game *game)
{
	free(game->str);
	free_all(game->map);
	close(game->fd);
	perror("\nclean up all after error;");
}

int check_border(t_game *game, int i)
{
	int j = 0;
	while (game->map[i][j])
	{
		if (game->map[i][j] != '1')
			return 0;
		j++;
	}
	return 1;
}

int	check_rectangle(t_game *game)
{
	int i = 0;
	int last_row = game->num_line - 1;
	while (i <= last_row )
	{
		if ((i != game->num_line - 1) && ft_strlen(game->map[i]) != ft_strlen(game->map[i + 1]))
			return(0);
		if ((i == 0 || i == last_row) && !check_border(game, i))
			return 0;
		if (game->map[i][0] != '1' || game->map[i][ft_strlen(game->map[i]) - 1] != '1')
			return 0;
		i++;
	}
	size_t len = ft_strlen(game->str);
	if (game->str[len - 1] == '\n')
		return (0);
	return (1);

}

void	ft_counting_cpe(t_game *game, char count)
{
	if (count == 'C')
		game->count_collectable++;
	else if (count == 'E')
		game->count_exit++;
	else if (count == 'P')
		game->count_player++;
}


int check_wall_elements(t_game *game)
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


 void	flood_fill(size_t x, size_t y, size_t num_line, char **map)
{
	if (x < 0 || y < 0 || x > num_line || y > ft_strlen(map[0]))
		return ;
	if (map[x][y] == 'E')
		map[x][y] = '1';
	if (map[x][y] == '1' || map[x][y] == 'V')
		return ;
	map[x][y] = 'V';
	flood_fill(x + 1, y, num_line, map);
	flood_fill(x - 1, y, num_line, map);
	flood_fill(x, y + 1, num_line, map);
	flood_fill(x, y - 1, num_line, map);
}
int		test_ff(char **map)
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

int	check_ff(t_game game)
{
	int i, j;
	char **copy_map = ft_split(game.str, '\n');
	if (!copy_map)
		return 0;

	for (i = 0; copy_map[i]; i++)
		for (j = 0; copy_map[i][j]; j++)
			if (copy_map[i][j] == 'P')
			{
				flood_fill(i, j, game.num_line, copy_map);
				if (!test_ff(copy_map))
				{
					free_all(copy_map);
					return 0;
				}
			}
	free_all(copy_map);
	return 1;
}


int	result_check(t_game *game)
{
	char *new_line = NULL;
	char *tmp;

	while(1337)
	{
		new_line = get_next_line(game->fd);
		if (!new_line)
			break;
		tmp = game->str;
		game->str = ft_strjoin(game->str, new_line);
		free(tmp);
		if (!game->str || new_line[0] == '\n')
			return(free(game->str),free(new_line),close(game->fd), 0);
		free(new_line);
		game->num_line++;
	}
	game->map = ft_split(game->str,'\n');
	if (!game->map)
		return(handle_error(game), 0);
	if (!check_rectangle(game) || !check_wall_elements(game))
		return(handle_error(game), 0);
	if (!check_ff(*game))
		return(handle_error(game), 0);
	return (1);
}



int check_map(char *path, t_game *game) 
{
	game->fd = open(path,O_RDONLY);
	if (game->fd == -1)
	{
		perror("\noh there is a prblm in the file not open;");
		return 1;
	}
	game->str = NULL;
	game->num_line = 0;
	if (!result_check(game))
		return 0;
	return 1;
}

int is_valid_map(char *path, t_game *game)
{
	char *valid_extention = ".ber";
	if (ft_strncmp(path + ft_strlen(path) - 4, valid_extention ,4))
	{
		perror("\n Oh soory you file has prblm with extention.");
		return 0;
	}
	if (!check_map(path ,game))
	{
		perror("\n Oh sorry there is prblm in check_map function.");
		return 0;
	}
	return 1;
}

int main(int ac, char **av)
{
	t_game	game;
	char 	*map;
	if (ac != 2)
	{	
		perror("ops there is a probelm 1.0: ");
		return (1);
	}
	map = av[1];
	if (!is_valid_map(map, &game))
	{
		perror("ops there is a probelm 2.0: ");
		return (1);
	}
	printf("\nthe map is all correct now great; ");
	// if (!map_build(map)) //TODO: later on this one;
	// {
	// 	perror("ops there is a probelm 3.0: ");
	// 	free_map(game.map);
	// 	close(game.fd);
	// 	return 1;
	// }
	return 0;
}
