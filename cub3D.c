/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:00:18 by mjammie           #+#    #+#             */
/*   Updated: 2021/08/09 16:12:12 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	parse_map(t_all *all, t_lst *lst)
{
	int	i;

	i = 0;
	all->map_c = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) - all->count));
	all->map_c[ft_lstsize(lst) - all->count] = NULL;
	while (i < (all->count + 1))
	{
		lst = lst->next;
		i++;
	}
	i = 0;
	while (lst)
	{
		all->map_c[i] = lst->str;
		lst = lst->next;
		i++;
	}
	all->map_c[i] = NULL;
	// i = 0;
	// while (map->map[i] != NULL)
	// {
	// 	ft_putstr_fd(map->map[i], 1);
	// 	ft_putchar_fd('\n', 1);
	// 	i++;
	// }
}

void	set_coordinates(t_all *all, int i, int j)
{
	all->player.posX = (double)i + 0.5;
	all->player.posY = (double)j + 0.5;
	if (all->map[i][j] == 21) // E
	{
		all->player.dirX = 0;
		all->player.dirY = 1;
		all->player.planeX = 0.66;
		all->player.planeY = 0;
	}
	else if (all->map[i][j] == 30) // N
	{
		all->player.dirX = -1;
		all->player.dirY = 0;
		all->player.planeX = 0;
		all->player.planeY = 0.66;
	}
	else if (all->map[i][j] == 35) // S
	{
		all->player.dirX = 1;
		all->player.dirY = 0;
		all->player.planeX = 0;
		all->player.planeY = -0.66;
	}
	else if (all->map[i][j] == 39) // W
	{
		all->player.dirX = 0;
		all->player.dirY = -1;
		all->player.planeX = -0.66;
		all->player.planeY = 0;
	}
	all->map[i][j] = 0;
}

void	change_map_int(t_all *all, t_lst *lst)
{
	t_lst *h;
	int	i;
	int	j;
	int	c;

	i = 0;
	j = 0;
	c = 0;
	all->map = (int **)malloc(sizeof(int *) * (ft_lstsize(lst) - all->count));
	while (i < 8)
	{
		lst = lst->next;
		i++;
	}
	i = 0;
	h = lst;
	while (lst)
	{
		j = 0;
		all->map[i] = malloc(sizeof(int) * ft_strlen(lst->str));
		while (lst->str[j])
		{
			all->map[i][j] = lst->str[j] - 48;
			if (all->map[i][j] == -16)
				all->map[i][j] = 1;
			if (all->map[i][j] > 1 && all->map[i][j] != 2)
			{
				set_coordinates(all, i , j);
			}
			if (all->map[i][j] == 2)
			{
				all->sprites.x = i;
				all->sprites.y = j;
				all->map[i][j] = 1;
			}
			j++;
		}
		lst = lst->next;
		i++;
	}
}

void	check_lst(t_lst *lst, t_all *all)
{
	// int		count;
	t_lst	*head;
	int		i;

	i = 0;
	head = lst;
	// count = 0;
	while (lst)
	{
		if (check_key(lst->str) == 0)
		{
			printf("%s\n", lst->str);
			all->count++;
		}
		lst = lst->next;
	}
	all->count--;
	lst = head;
	printf("%d\n", all->count);
	parse_map(all, lst);
}

void	max_height_map(t_all *all)
{
	int	y;

	y = 0;
	all->map_max_width = 0;
	while (all->map_c[y])
	{
		if (all->map_max_width < ft_strlen(all->map_c[y]))
			all->map_max_width = ft_strlen(all->map_c[y]);
		y++;
	}
	all->map_max_height = y;
}

void	init_path(t_all *all)
{
	all->path->north_path = NULL;
	all->path->south_path = NULL;
	all->path->west_path = NULL;
	all->path->east_path = NULL;
	all->path->floor_colour = -1;
	all->path->celling_colour = -1;
	all->path->no_count = 0;
	all->path->so_count = 0;
	all->path->we_count = 0;
	all->path->ea_count = 0;
	all->path->f_count = 0;
	all->path->c_count = 0;
}

int	main(int argc, char **argv)
{
	t_all	*all;
	t_lst	*lst;
	t_lst	*head;
	int		fd;
	char	*line;
	// int		from;
	int		try_to_read;
	char	buf[10];

	all = malloc(sizeof(t_all));
	all->path = malloc(sizeof(t_paths));
	all->count = 0;
	all->player.posX = 0;
	all->player.posY = 0;
	all->player.prevX = 0;
	all->player.prevY = 0;
	// all->mouse.x = SCREEN_HEIGHT / 2;
	// all->mouse.y = SCREEN_WIDTH / 2;
	// all->mouse.x = -1;
	// all->prev_mouse.x = -1;

	init_path(all);
	if (argc == 2)
	{
		int from;
		from = ft_strlen(argv[1]) - 4;
		if (ft_strnstr(&argv[1][from], ".cub", 4) != 0)
		{
			fd = open(argv[1], O_RDONLY);
			if (fd != - 1)
			{
				try_to_read = read(fd, buf, 10);
				if (try_to_read == 0)
				{
					close(fd);
					ft_putstr_fd("Error\nEmpty file\n", 1);
					exit (1);
				}
			}
			else
			{
				close(fd);
				ft_putstr_fd("Error\nCouldn't open file\n", 1);
				exit (1);
			}
			close(fd);
		}
		else
		{
			ft_putstr_fd("Error\nFile must be .cub extension\n", 1);
			exit (1);
		}
	}
	else
	{
		ft_putstr_fd("Error\nNot enought arguments\n", 1);
		exit (1);		
	}
	fd = open(argv[1], O_RDONLY);	
	line = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&lst, ft_lstnew(line));
	head = lst;
	check_lst(lst, all);
	main_check(lst, all);
	parse_info(lst, all);
	change_map_int(all, lst);
	max_height_map(all);
	raycaster(all);
}
