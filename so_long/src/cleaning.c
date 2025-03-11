/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 03:33:38 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	cleanup_resources(t_game *game)
{
	if (game->raw_map)
		free(game->raw_map);
	free_all(game->map_grid);
	if (game->fd > 0)
		close(game->fd);
}

void	free_all(char **grid)
{
	int	row;

	row = 0;
	if (!grid)
		return ;
	while (grid[row])
	{
		free(grid[row]);
		row++;
	}
	free(grid);
}
void *ft_memset(void *b, int c, size_t len)
{
    unsigned char *ptr;
    
    ptr = (unsigned char*)b;
    while (len--)
        *ptr++ = (unsigned char)c;
    return (b);
}
