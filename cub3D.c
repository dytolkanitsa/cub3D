/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:00:18 by mjammie           #+#    #+#             */
/*   Updated: 2021/08/04 23:39:36 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	parse_map(t_map *map, t_lst *lst)
{
	int	i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) - 7));
	map->map[ft_lstsize(lst) - 7] = NULL;
	while (i < 8)
	{
		lst = lst->next;
		i++;
	}
	i = 0;
	while (lst)
	{
		map->map[i] = lst->str;
		lst = lst->next;
		i++;
	}
	map->map[i] = NULL;
	// i = 0;
	// while (map->map[i] != NULL)
	// {
	// 	ft_putstr_fd(map->map[i], 1);
	// 	ft_putchar_fd('\n', 1);
	// 	i++;
	// }
}

void	check_lst(t_lst *lst, t_map *map)
{
	int		count;
	t_lst	*head;
	int		i;

	i = 0;
	head = lst;
	count = 0;
	while (lst)
	{
		if (check_key(lst->str) == 0)
		{
			printf("%s\n", lst->str);
			count++;
		}
		lst = lst->next;
	}
	count--;
	printf("%d\n", count);
	lst = head;
	if (count != 7)
		exit (0);
	else
	{
		parse_map(map, lst);
	}
}

int	main(int argc, char **argv)
{
	t_lst	*lst;
	t_lst	*head;
	t_map	map;
	t_paths	path;
	int		fd;
	char	*line;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (0);
	line = NULL;
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&lst, ft_lstnew(line));
	}
	head = lst;
	lst->error = 0;
	
	// parse_map(&map, lst);
	check_lst(lst, &map);
	main_check(lst, map);
	parse_info(lst, &path, map);
	printf("%d\n",lst->error);
	// // while (lst)
	// {
	// 	printf("%s\n", lst->str);
	// 	lst = lst->next;
	// }
}
