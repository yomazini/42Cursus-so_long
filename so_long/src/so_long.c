/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 02:59:08 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int map_parsing(char *path, t_game *game)
{
	char *valid_extention = ".ber";
	if (ft_strncmp(path + ft_strlen(path) - 4, valid_extention ,4))
	{
		perror("\nCheck Extention.");
		return (0);
	}
	if (!map_validation(path ,game))
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_game	game;
	char 	*map;
	if (ac != 2)
	{	
		perror("\nError:");
		return (1);
	}
	map = av[1];
	if (!map_parsing(map, &game))
	{
		perror("\nError in map: ");
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
	return (0);
}
