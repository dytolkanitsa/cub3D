/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 01:39:35 by lgarg             #+#    #+#             */
/*   Updated: 2021/08/09 13:07:46 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	parse_info(t_lst *lst, t_all *all)
{
	int	i;

	i = 0;
	while (i < all->count)
	{
		get_path(lst->str, lst, all);
		lst = lst->next;
		i++;
	}
}