/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/09 16:55:07 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int map_checker(char *map, )
{

//return 0 if the map not valid 

// return 1 if the map valid


}

int map_build(char *map, t_game *game)
{
	
//return 0 if the map not valid 

// return 1 if the map valid
}
void	free_all(char **map)
{
	int i;

	i = 0;
	if (!map)
		return ;
	while(map[i])
	{
		
	}
}

int main(int ac, char **av)
{
	t_game	*game;
	char 	*map;
	if (ac != 2)
	{	
		perror("ops there is a probelm 1.0: ");
		return (1);
	}
	if (!map_checker(map, game))
	{
		perror("ops there is a probelm 2.0: ");
		return (1);
	}
	if (!map_build(map, game))
	{
		perror("ops there is a probelm 3.0: ");
		free_map(game->map);
		close(game->fd);
		return 1;
	}
}

// keychanges 
/*
work with ptr not value will edit directly
*/