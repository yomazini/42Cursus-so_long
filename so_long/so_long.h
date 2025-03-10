/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:13:40 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 16:51:51 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define BUFFER_SIZE 10
# define ESC_KEY 53 
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2

typedef struct s_map_data
{
	size_t			width;
	size_t			height;
	size_t			player_pos_x;
	size_t			player_pos_y;
	size_t			collectible_count;
	size_t			exit_count;
	size_t			player_count;
}					t_map_data;

typedef struct s_game
{
	int				fd;
	int				line_count;
	char			*raw_map;
	char			**map_grid;
	t_map_data		props;
	void			*mlx;
	void			*win;
	size_t			window_width;
	size_t			window_height;
	int				img_width;
	int				img_height;
	void			*textures[5];
	size_t			move_count;
}					t_game;

/* gnl functions */
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, size_t start, size_t len);

/* libtools functions */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);

/* cleaning functions */
void	cleanup_resources(t_game *game);
void	free_all(char **grid);

/* parsing functions */
int		validate_map_file(char *path, t_game *game);
int		process_map_content(t_game *game);
int		verify_map_shape(t_game *game);
int		check_wall_border(t_game *game, int line_idx);
int		validate_map_elements(t_game *game);
void	flood_fill_check(size_t x, size_t y, size_t max_lines, char **grid);
int		verify_remaining_elements(char **grid);
int		validate_map_path(t_game game);

/* this below for the mlx map building */

#endif 