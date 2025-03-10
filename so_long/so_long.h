/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:13:40 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 03:09:06 by ymazini          ###   ########.fr       */
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

typedef struct data_game
{
	int				fd;
	int				num_line;
	char			*str;
	char			**map;
	size_t			count_player;
	size_t			count_exit;
	size_t			count_collectable;
	void			*mlx;
	void			*win;
	size_t			ww;
	size_t			wh;
	int				iw;
	int				ih;
	void			*textures[5];
	size_t			row;
	size_t			col;
	size_t			moves;
	size_t			player_x;
	size_t			player_y;
}					t_game;

// gnl
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, size_t start, size_t len);
// libtools
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
// cleaning.c
void	handle_error(t_game *game);
void	free_all(char **map);
// parse1.c
int		map_validation(char *path, t_game *game);
int		map_validation2(t_game *game);
int		map_rectangle(t_game *game);
int		check_border(t_game *game, int i);
// parse2.c
int		is_element_valid(t_game *game);
void	ft_flood_fill(size_t x, size_t y, size_t num_line, char **map);
int		checking_new_map(char **map);
int		validating_new_map(t_game game);

/* this below for the mlx map building */

#endif 