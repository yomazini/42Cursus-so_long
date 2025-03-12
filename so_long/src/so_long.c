/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/12 22:25:48 by ymazini          ###   ########.fr       */
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

static int	process_map(char *path, t_game *game)
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

int	build_graphic_map(t_game *game)
{
	get_dimention_map(game);
	if (game->window_width > 1900 || game->window_height > 1100)
	{
		perror("\nError: Map dimensions too large");
		cleanup_resources(game);
		exit (1);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game->mlx), 0);
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "so_long");
	if (!game->win)
	{
		free(game->mlx);
		return (0);
	}
	imgs_to_map(game);
	create_map(game);
	mlx_hook(game->win, 2, 0, handling_the_keys, game);
	mlx_hook(game->win, ON_DESTROY, 0, window_exit, game);
	mlx_loop(game->mlx);
	return (1);
}

void	debug_checks(void);

int	main(int ac, char **av)
{
	t_game	game;

	atexit (debug_checks);
	if (ac != 2)
	{
		ft_putstr("\nError: Invalid arguments.\n");
		return (1);
	}
	if (!process_map(av[1], &game))
	{
		ft_putstr("\nError: Map validation Failed\n");
		return (1);
	}
	if (!build_graphic_map(&game))
	{
		cleanup_resources(&game);
		ft_putstr("\nError: Failed to initialize Graphics\n");
		return (1);
	}
	cleanup_resources(&game);
	return (0);
}

void	debug_checks(void)
{
    char cmd[256];
    pid_t pid = getpid();
    sprintf(cmd, "lsof -p %d", pid);
    ft_putstr("\n--- Debugging: Checking for leaks and open file descriptors ---\n");
    system("leaks so_long");
    system(cmd);
    ft_putstr("--- End of Debug Checks ---\n");
}