/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:01:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/08/02 17:54:03 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
// # define BAD_ARG
// # define BAD_FD
# define BAD_MAP 1 // не обрамляется единицами, посторонние символы, несколько символов игрока
# define DUBLICATE_TEX 2
# define DUBLICATE_RES 3
# define DUBLICATE_COLOUR 4
# define BAD_TEXTURE 5
# define BAD_COLOUR 6
# define INVALID_RES 7
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

//work with map
void	work_with_map(t_map *map, t_lst *lst);

void	main_check(t_lst *lst, t_map map);

void	parse_info(t_lst *lst, t_paths *path);
#endif