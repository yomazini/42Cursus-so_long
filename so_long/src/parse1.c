/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:15:17 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 03:08:46 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int map_validation(char *path, t_game *game)
{
	game->fd = open(path, O_RDONLY);
	if (game->fd == -1)
	{
		perror("\nProblem in fd");
		return (1);
	}
	game->str = NULL;
	game->num_line = 0;
	if (!map_validation2(game))
		return 0;
	return 1;
}

int	map_validation2(t_game *game)
{
	char *new_line = NULL;
	char *to_free;

	while(1337)
	{
		new_line = get_next_line(game->fd);
		if (!new_line)
			break;
		to_free = game->str;
		game->str = ft_strjoin(game->str, new_line);
		free(to_free);
		if (!game->str || new_line[0] == '\n')
			return(free(game->str),free(new_line),close(game->fd), 0);
		free(new_line);
		game->num_line++;
	}
	game->map = ft_split(game->str,'\n');
	if (!game->map)
		return(handle_error(game), 0);
	if (!map_rectangle(game) || !is_element_valid(game))
		return(handle_error(game), 0);
	if (!validating_new_map(*game))
		return(handle_error(game), 0);
	return (1);
}
int	map_rectangle(t_game *game)
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
