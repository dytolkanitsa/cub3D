/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:01:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/08/05 03:10:19 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
// # define BAD_ARG
// # define BAD_FD
# define BAD_MAP 1 // не обрамляется единицами, посторонние символы, несколько символов игрока
# define DUBLICATE_TEX 2
# define DUBLICATE_COLOUR 3
# define BAD_TEXTURE 4
# define BAD_KEY 5
# define BAD_COLOUR 6
# define NOT_ENOUGHT_TEX 7
# define NOT_ENOUGHT_COLOUR 8
// # define INVALID_KEY
// # define INVALID_MAIN_ARG

typedef struct s_paths
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_colour;
	int		celling_colour;
}	t_paths;

typedef struct s_map
{
	char	**map;
}				t_map;

typedef struct s_lst
{
	char			*str;
	int				error;
	struct s_lst	*next;
}				t_lst;


//utils
t_lst	*ft_lstlast(t_lst *lst);
int		ft_lstsize(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
t_lst	*ft_lstnew(void *content);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_splitlen(char **str);
int		ft_strncmp(const char *str1, const char *str2, size_t num);

//work with map
void	work_with_map(t_map *map, t_lst *lst);


// parser //check_map
void	main_check(t_lst *lst, t_map map);
void	parse_info(t_lst *lst, t_paths *path, t_map map);
int		check_key(char *line);
int		right_key(t_lst *lst);
int		dublicate_colour(t_lst *lst);
int		dublicate_texture(t_lst *lst);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		check_last_corner(char *line, char *last);
int		check_first_corner(char *line, char *next);
int		check_corners(t_lst *lst, t_map map);
int		if_surrounded_by_wals(t_lst *lst, t_map map);
int		check_first_last_line(char *line);
int		check_line_for_wals(char *line, char *next, char *last);
char 	ft_check(char c, const char *set);
int		ft_splitlen(char **str);

// parse_info
int		ft_atoi(char *str);
void	get_path(char *line, t_paths *path, t_lst *lst, t_map map);
int		get_colour(char *line, t_lst *lst, t_map map);
char	*ft_strtrim(char const *s, const char *set);
char	**ft_split(char const *s, char c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *str1, const char *str2, size_t num);
#endif