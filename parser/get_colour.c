/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 03:03:50 by lgarg             #+#    #+#             */
/*   Updated: 2021/08/05 03:03:57 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_colour(char *line, t_lst *lst, t_map map)
{
	char **temp;
	int	red;
	int	green;
	int	blue;
	// int	res;

	if (!line)
		return (0);
	temp = ft_split(line, ',');
	if (ft_splitlen(temp) != 3)
	{
		lst->error = BAD_COLOUR;
		main_check(lst, map);
	}
	int	i;
	int	j;

	i = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (!ft_isdigit(temp[i][j]))
			{
				lst->error = BAD_COLOUR;
				main_check(lst, map);	
			}
			j++;
		}
		i++;
	}
	red = ft_atoi(temp[0]);
	green = ft_atoi(temp[1]);
	blue = ft_atoi(temp[2]);
	free(temp);
	if (red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0)
	{
		lst->error = BAD_COLOUR;
		main_check(lst, map);
	}
	// res = make_rgb_colour(red, green, blue);
// то, что ниже, это кодирование отдельных компонентов RGB в целочисленное значение с помощью битового сдвига
	return (red << 16 | green << 8 | blue);
}