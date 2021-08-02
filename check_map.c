/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:49:33 by lgarg             #+#    #+#             */
/*   Updated: 2021/08/02 20:12:27 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	right_simbols_in_map(t_lst *lst, t_map *map)
{
	int	i;
	int	j;

	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			
		}
	}
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
