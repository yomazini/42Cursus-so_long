/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 20:28:42 by ymazini          ###   ########.fr       */
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

void get_dimention_map(t_game *game)
{
    int row = 0;
    int col = 0;
    while (game->map_grid[row])
    {
        col = ft_strlen(game->map_grid[row]);
        row++;
    }
    game->window_width = col * tile_size;
    game->window_height = row * tile_size;
    game->img_width = game->window_width;
    game->img_height = game->window_height;
}

int handling_the_keys(int key_pressed, t_game *game);

void	put_xpm_element(t_game *game, char *name_of_xpm, int order)
{
	game->textures[order] = mlx_xpm_file_to_image(game->mlx,name_of_xpm, &game->props.width ,&game->props.height);
	if (!game->textures[order])
	{
		perror("Error In Texture: ");
		free_all(game->map_grid);
		free(game->mlx);
		free(game->win);
		exit(1);
	}
}

void	imgs_to_map(t_game *game)
{
	put_xpm_element(game, "./textures/route.xpm", 0);
	put_xpm_element(game, "./textures/wall.xpm", 1);
	put_xpm_element(game, "./textures/exit.xpm", 2);
	put_xpm_element(game, "./textures/nud.xpm", 3);
	put_xpm_element(game, "./textures/player.xpm", 4);
}
void	player_moves(t_game *game,unsigned int key_pressed);
void create_map(t_game *game)
{
    int row = 0;
    
    while (game->map_grid[row])
    {
        int col = 0;
        while (game->map_grid[row][col])
        {
            int x = col * tile_size;
            int y = row * tile_size;
            mlx_put_image_to_window(game->mlx, game->win, game->textures[0], x, y);
            if (game->map_grid[row][col] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->textures[1], x, y);
            else if (game->map_grid[row][col] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->textures[2], x, y);
            else if (game->map_grid[row][col] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->textures[3], x, y);
            else if (game->map_grid[row][col] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->textures[4], x, y);
                
            col++;
        }
        row++;
    }
}

int window_exit(t_game *game)
{
    int i;
   if (game->fd > 0)
    {
        close(game->fd);
        game->fd = -1;
    }

    for (i = 0; i < 5; i++)
    {
        if (game->textures[i])
            mlx_destroy_image(game->mlx, game->textures[i]);
    }
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    free_all(game->map_grid);
    if (game->raw_map)
        free(game->raw_map);
    
    exit(0);
    return 0;
}

void	player_lookup(t_game *game)
{
	int row;
	int col;
	
	row = 0;
	while (game->map_grid[row])
	{
		col = 0;
		while (game->map_grid[row][col])
		{
			if (game->map_grid[row][col] == 'P')
			{
				game->props.player_pos_x = row;
				game->props.player_pos_y = col;	
				return ;
			}
			col++;
		}
		row++;
	}
}

void	print_moves(t_game *game)
{
	char *nmr_moves;
	nmr_moves = ft_itoa(game->move_count);
	ft_putstr(">Player moves: ");
	ft_putstr(nmr_moves);
	ft_putstr("\n");
	free(nmr_moves);
}

int build_graphic_map(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return 0;
        
    get_dimention_map(game);
    if (game->window_width > 5120 || game->window_height > 2880)
    {
        perror("\nError: Map dimensions too large");
        free(game->mlx);
        return 0;
    }
    
    game->win = mlx_new_window(game->mlx, game->window_width, game->window_height, "So_Long");
    if (!game->win)
    {    
        free(game->mlx);
        return 0;
    }
    
    imgs_to_map(game);
    create_map(game);
    mlx_hook(game->win, ON_KEYDOWN, KeyPressMask, handling_the_keys, game);
    mlx_hook(game->win, ON_DESTROY, 0, window_exit, game);
    mlx_loop(game->mlx);
    return 1;
}

int handling_the_keys(int key_pressed, t_game *game)
{
    if (key_pressed == ESC_KEY)
        window_exit(game);
    else if (key_pressed == W_KEY || key_pressed == A_KEY || 
             key_pressed == S_KEY || key_pressed == D_KEY)
        player_moves(game, key_pressed);
    return (1);
}

void player_new_position(t_game *game, int new_x_position, int new_y_position)
{
    if (new_x_position < 0 || new_y_position < 0 || 
        new_x_position >= game->line_count || 
        new_y_position >= (int)ft_strlen(game->map_grid[0]))
        return;
    
    char target = game->map_grid[new_x_position][new_y_position];
    if (target == '1')
        return;
    if (target == 'E') {
        if (game->props.collectible_count == 0) {
            game->move_count++;
            print_moves(game);
            ft_putstr("\nCongrats: You Win!");
            window_exit(game);
        }
        return;
    }
    if (target == 'C')
        game->props.collectible_count--;
    game->map_grid[new_x_position][new_y_position] = 'P';
    game->map_grid[game->props.player_pos_x][game->props.player_pos_y] = '0';
    game->move_count++;
    
    game->props.player_pos_x = new_x_position;
    game->props.player_pos_y = new_y_position;
    
    mlx_clear_window(game->mlx, game->win);
    create_map(game);
    print_moves(game);
}

void player_moves(t_game *game, unsigned int key_pressed)
{
    player_lookup(game);
    
    if (key_pressed == D_KEY)
        player_new_position(game, game->props.player_pos_x, game->props.player_pos_y + 1);
    else if (key_pressed == A_KEY)
        player_new_position(game, game->props.player_pos_x, game->props.player_pos_y - 1);
    else if (key_pressed == W_KEY)
        player_new_position(game, game->props.player_pos_x - 1, game->props.player_pos_y);
    else if (key_pressed == S_KEY)
        player_new_position(game, game->props.player_pos_x + 1, game->props.player_pos_y);
}

#include "../so_long.h"

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


int main(int ac, char **av)
{
    t_game game;
	
    ft_memset(&game, 0, sizeof(t_game));
    atexit(debug_checks);
  // Register debug_checks() to run when main exits

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
       For debugging, we cleanup immediately to check that all resources are freed.
    */
    cleanup_resources(&game);
    ft_putstr("\nExiting game. Resources cleaned up.\n\n\n");
	close(game.fd);
    return (0);
}


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
