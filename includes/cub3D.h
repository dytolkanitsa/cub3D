/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:01:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/08/09 16:19:05 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../minilibx_mms_20200219/mlx.h"
# include <math.h>
# include <unistd.h>
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define texWidth 64
# define texHeight 64

# define BAD_MAP 1
# define DUBLICATE_TEX 2
# define DUBLICATE_COLOUR 3
# define BAD_TEXTURE 4
# define BAD_KEY 5
# define BAD_COLOUR 6
# define NOT_ENOUGHT_TEX 7
# define NOT_ENOUGHT_COLOUR 8

# define GREY	0x808080
# define PURPLE	0xb677d4
# define BLUE	0x55b1d9
# define RED	0xe06060
# define GREEN	0x7ed477
# define YELLOW	0xeaf279
# define PI		3.1416

typedef struct s_paths
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_colour;
	int		celling_colour;
	int		no_count;
	int		so_count;
	int		we_count;
	int		ea_count;
	int		f_count;
	int		c_count;
	int		red;
	int		green;
	int		blue;
}	t_paths;

typedef	struct	s_vectors
{
	int		x;
	int		y;
}	t_vectors;

typedef struct s_lst
{
	char			*str;
	int				error;
	struct s_lst	*next;
}				t_lst;

typedef struct s_mini
{
	double		dir_x;
	double		dir_y;
	double		pa;
	double		start;
	double		end;
	double		x;
	double		y;
	int			on;
}				t_mini;

typedef struct s_player
{
	int			x;
	int			y;
	double		pa;
	double		posX;
	double		prevX;
	double		posY;
	double		prevY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}				t_player;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texture;
}				t_sprite;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct s_data
{
	void	*img;
	void	*img_player;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// typedef struct s_hooks
// {
// 	int UP;
// 	int DOWN;
// 	int LEFT;
// 	int RIGHT;
// } t_hooks;

// typedef struct s_textures
// {
// 	unsigned int	**colors_north;
// 	unsigned int	**colors_south;
// 	unsigned int	**colors_west;
// 	unsigned int	**colors_east;
// }				t_textures;


typedef struct s_all
{
	// t_hooks		hok;
	t_player		player;
	t_data			img;
	t_mlx			mlx;
	t_paths			*path;
	char			**map_c;
	int				**map;
	int				**colors_north;
	int				**colors_south;
	int				**colors_west;
	int				**colors_east;
	int				**colors_sprite;
	int				count;

	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit; 
	int		side;

	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double 	wallX;

	int		color;

	int		x;
	int		i;
	int		exit;

	double moveSpeed;
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;

	int	j;
	t_data			img_map;
	t_mini			mini;
	t_sprite		sprites;
	t_vectors		mouse;
	t_vectors		prev_mouse;
	int				map_max_width;
	int				map_max_height;
}				t_all;

//utils
t_lst	*ft_lstlast(t_lst *lst);
int		ft_lstsize(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
t_lst	*ft_lstnew(void *content);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

//raycast
void	raycaster(t_all *all);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	print_map(t_all *all);

// parser //check_map
void	main_check(t_lst *lst, t_all *all);
void	parse_info(t_lst *lst, t_all *all);
int		check_key(char *line);
int		right_key(t_lst *lst);
int		dublicate_colour(t_lst *lst, t_all *all);
int		dublicate_texture(t_lst *lst, t_all *all);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		check_last_corner(char *line, char *last);
int		check_first_corner(char *line, char *next);
int		check_corners(t_lst *lst, t_all *all);
int		if_surrounded_by_wals(t_lst *lst, t_all *all);
int		check_first_last_line(char *line);
int		check_line_for_wals(char *line, char *next, char *last);
char	ft_check(char c, const char *set);
int		ft_splitlen(char **str);

// parse_info
int		ft_atoi(char *str);
void	get_path(char *line, t_lst *lst, t_all *all);
int		get_colour(char *line, t_lst *lst, t_all *all);
char	*ft_strtrim(char const *s, const char *set);
char	**ft_split(char const *s, char c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *str1, const char *str2, size_t num);

void	print_mini_map(t_all *all);
void	print_img(t_data *img, int x, int y, int color);
int		key_hook_mini(int keycode, t_all *all);
void	print_player(t_all *all, int color);

#endif