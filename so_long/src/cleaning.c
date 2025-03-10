/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 03:04:03 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	handle_error(t_game *game)
{
	free(game->str);
	free_all(game->map);
	close(game->fd);
}

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
