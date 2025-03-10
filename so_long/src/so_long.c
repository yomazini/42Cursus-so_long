/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 16:55:50 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static	int	validate_file_extension(char *path)
{
	char	*valid_extenstion;
	int		path_len;

	valid_extenstion = ".ber";
	path_len = ft_strlen(path);
	if (path_len < 4)
		return (0);
	return (ft_strncmp(path + path_len - 4, valid_extenstion, 4) == 0);
}

int	process_map(char *path, t_game *game)
{
	if (!validate_file_extension(path))
	{
		perror("\nfile extension Problem:");
		return (0);
	}
	game->props.collectible_count = 0;
	game->props.exit_count = 0;
	game->props.player_count = 0;
	if (!validate_map_file(path, game))
	{
		perror("\nMap validation failed");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		perror("\nError:");
		return (1);
	}
	if (!process_map(av[1], &game))
		return (1);
	printf("\nMap validation successful.");
	cleanup_resources(&game);
	// Future implementation of map building with mlx
	// if (!build_graphic_map(&game)) {
	//     perror("\nError initializing graphics");
	//     cleanup_resources(&game);
	//     return (1);
	// }
	return (0);
}
