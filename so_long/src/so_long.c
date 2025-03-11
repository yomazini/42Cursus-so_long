/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:21 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 02:43:59 by ymazini          ###   ########.fr       */
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

/*		 ----- this is for building the map  -----		*/


void	get_dimention_map(t_game *game)
{
	int col;
	int row;

	row = 0;
	while(game->map_grid[row])
	{
		col = 0;
		while (game->map_grid[row][col])
			col++;		
		row++;
	}
	game->img_width = tile_size * row;
	game->img_height = tile_size * col;
}
int	handling_the_keys(t_game *game, unsigned int key_pressed);

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
	put_xpm_element(game, "./textures/wall.xpm", 0);
	put_xpm_element(game, "./textures/wall.xpm", 1);
	put_xpm_element(game, "./textures/exit.xpm", 2);
	put_xpm_element(game, "./textures/nud.xpm", 3);
	put_xpm_element(game, "./textures/player.xpm", 4);
}
void	player_moves(t_game *game,unsigned int key_pressed);

void	create_map(t_game *game) //TODO: 1.2 
{
	int row = 0;
	int col;
	
	game->props.width = 0;
	game->props.height = 0;
	while (game->map_grid[row])
	{
		row = game->props.width * tile_size;
		while (game->map_grid[row][col])
		{
			col = game->props.height * tile_size;
			if (game->map_grid[row][col] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->textures[0],row,col);
			if (game->map_grid[row][col] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->textures[1], row, col);
			if (game->map_grid[row][col] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->textures[2], row, col);
			if (game->map_grid[row][col] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->textures[3], row, col);
			if (game->map_grid[row][col] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->textures[4], row, col);
			col++;
		}
		row++;
	}
}

int	window_exit(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->win);
	free_all(game->map_grid);
	free(game->mlx);
	close(game->fd);
	return (1);
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
}

 int	build_graphic_map(t_game *game)
{
	game->mlx = mlx_init();
	if(!game->mlx)
		return 0;
	get_dimention_map(game);
	if (game->img_width > 2304 || game->img_height > 4096)
	{
		perror("\ncheck the dimentions");
		free(game->mlx);
		return 0;
	}
	game->win = mlx_new_window(game->mlx,game->img_width, game->img_height, "So_Long");
	if (!game->win)
	{	
		return (free(game->mlx), 0);
	}
	imgs_to_map(game);
	create_map(game);
	game->move_count = 0;
	mlx_hook(game->mlx, ON_KEYDOWN, KeyPressMask , handling_the_keys, game);
	mlx_hook(game->mlx, ON_DESTROY, KeyPressMask , window_exit, game);
	mlx_loop(game->mlx);
	return(1);
}
int	handling_the_keys(t_game *game, unsigned int key_pressed)
{
	if (key_pressed == ESC_KEY)
	{
		window_exit(game);
	}
	else if (key_pressed == W_KEY|| key_pressed == A_KEY || key_pressed == S_KEY || key_pressed == D_KEY )
	{
		player_moves(game, key_pressed);
	}
	return (1);
}

void	player_new_position(t_game *game, int new_x_position, int new_y_position)
{
	if (game->map_grid[new_x_position][new_y_position] == '0')
	{
		game->map_grid[new_x_position][new_y_position] = 'P';
		game->map_grid[game->props.player_pos_x][game->props.player_pos_y] = '0';
		game->move_count++;
	}
	if (game->map_grid[new_x_position][new_y_position]== 'C')
	{
		game->map_grid[new_x_position][new_y_position] = 'P';
		game->map_grid[game->props.player_pos_x][game->props.player_pos_y] = '0';
		game->move_count++;
		game->props.collectible_count--;
	}
	if (game->map_grid[new_x_position][new_y_position] == 'E' && game->props.collectible_count == 0)
	{
		ft_putstr("\nCongrats: You Win.");	
		window_exit(game);
	}
	if (game->map_grid[new_x_position][new_y_position] == '1')
		return ;
	if (game->map_grid[new_x_position][new_y_position] == 'E' && game->props.collectible_count != 0)
		return ;
	//call biuld_map again to build it again
	build_graphic_map(game);
	//count the movesfunctions 
	print_moves(game);
}

void	player_moves(t_game *game,unsigned int key_pressed)
{
	player_lookup(game);
	if (key_pressed == D_KEY)
		player_new_position(game, game->props.player_pos_x + 1,  game->props.player_pos_y);
	if (key_pressed == A_KEY)
		player_new_position(game, game->props.player_pos_x - 1,  game->props.player_pos_y);
	if (key_pressed == W_KEY)
		player_new_position(game, game->props.player_pos_x,  game->props.player_pos_y + 1);
	if (key_pressed == S_KEY)
		player_new_position(game, game->props.player_pos_x,  game->props.player_pos_y - 1);
}

/*
Width: 5120 pixels ÷ 50 pixels/tile = 102.4 tiles
Height: 2880 pixels ÷ 50 pixels/tile = 57.6 tiles
	so max is 102 tiles in rows and 57 in col
*/

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		perror("\nError:");
		return (1);
	}
	if (!process_map(av[1], &game))
	{	
		//cleanup_resources(&game);
		return (1);
	}
	printf("\nMap validation successful.");
	// Future implementation of map building with mlx
	if (!build_graphic_map(&game)) 
	{
	    perror("\nError initializing graphics");
	    cleanup_resources(&game);
	    return (1);
	}
	return (0);
}
