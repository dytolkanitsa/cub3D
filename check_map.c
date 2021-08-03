/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:49:33 by lgarg             #+#    #+#             */
/*   Updated: 2021/08/03 20:36:14 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

char static	ft_check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	right_simbols_in_map(t_lst *lst, t_map map) // валидные символы
{
	int	i;
	int	j;

	i = 0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j])
		{
			if (!ft_check(map.map[i][j], "10 NESW"))
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
			j++;
		}
		i++;
	}
	return(0); // хорошо
}

int	how_many_players(t_lst *lst, t_map map) // больше одного игрока
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j])
		{
			if (ft_check(map.map[i][j], "NSEW"))
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		lst->error = BAD_MAP;
		return (1); // плохо
	}
	return (0); // хорошо
}

int	check_line_for_wals(char *line, char *next, char *last) // все стены единички
{
	int	i;

	i = 0;
	printf("%s\n", line);
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (!ft_check(line[i], " 10NWSE") || ((line[i + 1] == ' ' \
							|| line[i - 1] == ' ') && line[i] != '1'))
			return (1);
		if ((line[i] == '0' && next[i] == ' ') \
							|| (line[i] == '0' && last[i] == ' '))
			return (1);
		i++;
	}
	return (0);
}

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_first_last_line(char *line) // чек верхней и нижней строки
{
	int	i;

	i = 0;
	printf("%s\n", line);
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (!ft_check(line[i], " 1") || ((line[i + 1] == ' ' || line[i - 1] == ' ') && line[i] != '1'))
			return (1);
		i++;
	}
	return (0);
}

int	if_surrounded_by_wals(t_lst *lst, t_map map)
{
	int	i;
	int	len;

	len = ft_splitlen(map.map);
	printf("%d\n", len);
	i = 0;
	while (map.map[i])
	{
		if (i == 0 || i == len - 1)
		{
			printf("tut\n");
			if (check_first_last_line(map.map[i]))
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
			else
				i++;
		}
		else 
		{
			printf("zdes\n");
			if (check_line_for_wals(map.map[i], map.map[i + 1], map.map[i - 1]))
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
		}
		i++;
	}
	return (0); // хорошо
}

int	check_first_corner(char *line, char *next)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (((!line[i - 1] || line[i - 1] == ' ') || (!line[i + 1] || line[i + 1] == ' ')) && (next[i] != '1' || next[i] != '1'))
			return (1);
		i++;
	}
	return (0);
}

int	check_last_corner(char *line, char *last)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (((!line[i - 1] || line[i - 1] == ' ') || (!line[i + 1] || line[i + 1] == ' ')) && (last[i] != '1' || last[i] != '1'))
			return (1);
		i++;
	}
	return (0);
}

int	check_corners(t_lst *lst, t_map map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_splitlen(map.map);
	while (map.map[i])
	{
		if (i == 0)
		{
			if (check_first_corner(map.map[i], map.map[i + 1]))
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
			else
				i++;
		}
		else if (i == len - 1)
		{
			if (check_last_corner(map.map[i], map.map[i - 1]))
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
			else
				i++;
		}
		else
		{
			if (check_first_corner(map.map[i], map.map[i + 1]))
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
			else
				i++;
		}
		// j = 0;
		// while (map.map[i][j] == ' ')
		// 	j++;
		// while (map.map[i][j])
		// {
		// 	if (       (   (!map.map[i][j - 1] || map.map[i][j - 1] == ' ') || (!map.map[i][j + 1] || map.map[i][j + 1] == ' ')  )     &&     (map.map[i + 1][j] != '1' || map.map[i - 1][j] != '1'))
		// 	{
		// 		lst->error = BAD_MAP;
		// 		return (1); // плохо
		// 	}
		// 	j++;
		// }
		i++;
	}
	return (0);
}

void	check_map(t_lst *lst)
{
	if (lst->error == BAD_MAP)
		ft_putstr_fd("Error: Map error\n", 1);
	else if (lst->error == DUBLICATE_TEX)
		ft_putstr_fd("Error: Dublicte texture\n", 1);
	else if (lst->error == DUBLICATE_RES)
		ft_putstr_fd("Error: Dublicte resolution\n", 1);
	else if (lst->error == DUBLICATE_COLOUR)
		ft_putstr_fd("Error: Dublicate colour\n", 1);
	else if (lst->error == BAD_TEXTURE)
		ft_putstr_fd("Error: Texture error\n", 1);
	else if (lst->error == BAD_COLOUR)
		ft_putstr_fd("Error: Colour error\n", 1);
	else if (lst->error == INVALID_RES)
		ft_putstr_fd("Error: Invalid resolution\n", 1);
	ft_putstr_fd("Quit cub3D\n", 1);
	exit (0);
}

void	main_check(t_lst *lst, t_map map)
{
	// if (right_simbols_in_map(lst, map) == 1 || how_many_players(lst, map) == 1 || if_surrounded_by_wals(lst, map) == 1 \
	// ||	check_nr_corner(lst, map) == 1)
	if (check_corners(lst, map) == 1)
		check_map(lst);
	else
		printf("everything is ok");
}