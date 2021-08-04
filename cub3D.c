/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:00:18 by mjammie           #+#    #+#             */
/*   Updated: 2021/08/02 20:05:57 by lgarg            ###   ########.fr       */
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
	parse_map(&map, lst);
	main_check(lst, map);
	parse_info(lst, &path);
	// // while (lst)
	// {
	// 	printf("%s\n", lst->str);
	// 	lst = lst->next;
	// }
}
