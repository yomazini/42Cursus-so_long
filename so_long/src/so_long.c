/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 21:24:49 by ymazini          ###   ########.fr       */
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

void	debug_checks(void);

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));//remove it later
	atexit (debug_checks);
	if (ac != 2)
	{
		ft_putstr("\nError: Invalid arguments. Usage: ./so_long map.ber\n");
		return (1);
	}
	if (!process_map(av[1], &game))
	{
		ft_putstr("\nError: Map validation failed\n");
		return (1);
	}
	ft_putstr("\nMap validation successful. Starting game...\n");
	if (!build_graphic_map(&game))
	{
		ft_putstr("\nError: Failed to initialize graphics\n");
		cleanup_resources(&game);
		return (1);
	}
	/* 
	   Game loop and interactions would go here.
	   For debugging, we cleanup immediately to 
	   check that all resources are freed.
	*/
	cleanup_resources(&game);
	return (0);
}

/* --------  */
void debug_checks(void)
{
    char cmd[256];
    pid_t pid = getpid();
    sprintf(cmd, "lsof -p %d", pid);
    ft_putstr("\n--- Debugging: Checking for leaks and open file descriptors ---\n");
    system("leaks so_long");
    system(cmd);
    ft_putstr("--- End of Debug Checks ---\n");
}

// int main(int ac, char **av)
// {
//     t_game game;
	
//     ft_memset(&game, 0, sizeof(t_game));
//     atexit(debug_checks);
//   // Register debug_checks() to run when main exits

//     if (ac != 2)
//     {
//         ft_putstr("\nError: Invalid arguments. Usage: ./so_long map.ber\n");
//         return (1);
//     }

//     if (!process_map(av[1], &game))
//     {
//         ft_putstr("\nError: Map validation failed\n");
//         return (1);
//     }

//     ft_putstr("\nMap validation successful. Starting game...\n");

//     if (!build_graphic_map(&game))
//     {
//         ft_putstr("\nError: Failed to initialize graphics\n");
//         cleanup_resources(&game);
//         return (1);
//     }

//     /* 
//        Game loop and interactions would go here.
//        For debugging, we cleanup immediately to check that all resources are freed.
//     */
//     cleanup_resources(&game);
//     ft_putstr("\nExiting game. Resources cleaned up.\n\n\n");
// 	close(game.fd);
//     return (0);
// }


// int main(int ac, char **av)
// {
//     t_game game;
//     ft_memset(&game, 0, sizeof(t_game));

//     if (ac != 2)
//     {
//         ft_putstr("\nError: Invalid arguments. Usage: ./so_long map.ber\n");
//         return (1);
//     }
    
//     if (!process_map(av[1], &game))
//     {    
//         ft_putstr("\nError: Map validation failed\n");
//         return (1);
//     }
    
//     ft_putstr("\nMap validation successful. Starting game...\n");
    
//     if (!build_graphic_map(&game)) 
//     {
//         ft_putstr("\nError: Failed to initialize graphics\n");
//         cleanup_resources(&game);
//         return (1);
//     }
//     return (0);
// }
