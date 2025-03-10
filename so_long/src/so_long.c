/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 03:46:21 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int validate_file_extension(char *path)
{
	char	*valid_extenstion = ".ber";
	size_t path_len = ft_strlen(path);
	
	if (path_len < 4)
		return (0);
	return (ft_strncmp(path + path_len - 4, valid_extenstion, 4) == 0);
}

int process_map(char *path, t_game *game)
{
	// Check file extension
	if (!validate_file_extension(path))
	{
		perror("\nInvalid file extension: must be .ber");
		return (0);
	}
	
	// Initialize game structure
	game->props.collectible_count = 0;
	game->props.exit_count = 0;
	game->props.player_count = 0;
	game->move_count = 0;
	
	// Validate map content
	if (!validate_map_file(path, game))
	{
		perror("\nMap validation failed");
		return (0);
	}
	
	return (1);
}

int main(int ac, char **av)
{
	t_game	game;
	
	// Check correct number of arguments
	if (ac != 2)
	{	
		perror("\nError: Usage: ./so_long <map_file.ber>");
		return (1);
	}
	
	// Process and validate map
	if (!process_map(av[1], &game))
	{
		return (1);
	}
	
	printf("\nMap validation successful! All checks passed.");
	
	// Clean up resources
	cleanup_resources(&game);
	
	// Future implementation of map building with mlx
	// if (!build_graphic_map(&game)) {
	//     perror("\nError initializing graphics");
	//     cleanup_resources(&game);
	//     return (1);
	// }
	
	return (0);
}
