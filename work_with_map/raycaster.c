/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 13:55:42 by mjammie           #+#    #+#             */
/*   Updated: 2021/08/08 11:14:37 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_win(void)
{
	ft_putstr_fd("Close window\n", 1);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	texpixcolor(t_data *img, int x, int y)
{
	char			*addr;
	unsigned int	color;

	addr = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int*)addr;
	return (color);
}

void	optimization_color_img(t_all *all, int ***arr, char *path)
{
	int	n;
	int	m;
	int	x;
	int	y;
	t_data	newImg;

	x = -1;
	n = 0;
	m = 0;
	if (!(newImg.img = mlx_xpm_file_to_image(all->mlx.mlx, path, &n, &m))) 
	{
		printf("Error\nWrong path to texture!!!\n");
		exit(0);
	}
	newImg.addr = mlx_get_data_addr(newImg.img, &newImg.bits_per_pixel, &newImg.line_length, &newImg.endian);
	(*arr) = (int **)malloc(sizeof(int*) * n);
	while (++x < texWidth) 
	{
		y = -1;
		(*arr)[x] = (int *)malloc(sizeof(int) * m);
  		while (++y < texHeight)
			  (*arr)[x][y] = texpixcolor(&newImg, x, y);
	}
}

void print(t_all *all) 
{
	// double	cameraX;
	// double	rayDirX;
	// double	rayDirY;
	// double	sideDistX;
	// double	sideDistY;
	// double	deltaDistX;
	// double	deltaDistY;
	// double	perpWallDist;
	// int		mapX;
	// int		mapY;
	// int		stepX;
	// int		stepY;
	// int		hit; 
	// int		side;

	// int		lineHeight;
	// int		drawStart;
	// int		drawEnd;
	// double 	wallX;

	// int		color;

	// int		x;
	// int		i;

	all->x = 0;
	all->color = 0;
	optimization_color_img(all, &all->colors_north, all->path->north_path);
	optimization_color_img(all, &all->colors_south, all->path->south_path);
	optimization_color_img(all, &all->colors_west, all->path->west_path);
	optimization_color_img(all, &all->colors_east, all->path->east_path);
	optimization_color_img(all, &all->colors_sprite, "textures/barrel.xpm");
	double step = 0;
	double texPos = 0;
	int texY = 0;
	while (all->x < SCREEN_WIDTH)
	{
		all->cameraX = 2 * all->x / (double)SCREEN_WIDTH - 1;
		all->rayDirX = all->player.dirX + all->player.planeX * all->cameraX;
		all->rayDirY = all->player.dirY + all->player.planeY * all->cameraX;
		all->mapX = (int)(all->player.posX);
		all->mapY = (int)(all->player.posY);
		all->deltaDistX = fabs(1 / all->rayDirX);
		all->deltaDistY = fabs(1 / all->rayDirY);
		all->hit = 0; 
		if(all->rayDirX < 0)
		{
			all->stepX = -1;
			all->sideDistX = (all->player.posX - all->mapX) * all->deltaDistX;
		}
		else
		{
			all->stepX = 1;
			all->sideDistX = (all->mapX + 1.0 - all->player.posX) * all->deltaDistX;
		}
		if(all->rayDirY < 0)
		{
			all->stepY = -1;
			all->sideDistY = (all->player.posY - all->mapY) * all->deltaDistY;
		}
		else
		{
			all->stepY = 1;
			all->sideDistY = (all->mapY + 1.0 - all->player.posY) * all->deltaDistY;
		}
		while (all->hit == 0)
		{
			if (all->sideDistX < all->sideDistY)
			{
				all->sideDistX += all->deltaDistX;
				all->mapX += all->stepX;
				all->side = 0;
			}
			else
			{
				all->sideDistY += all->deltaDistY;
				all->mapY += all->stepY;
				all->side = 1;
			}
			if (all->map[all->mapX][all->mapY] > 0)
			{
				all->hit = 1;
			}
		}
		if (all->side == 0)
			all->perpWallDist = (all->mapX - all->player.posX + (1 - all->stepX) / 2) / all->rayDirX;
		else
			all->perpWallDist = (all->mapY - all->player.posY + (1 - all->stepY) / 2) / all->rayDirY;
		all->lineHeight = (int)(SCREEN_HEIGHT / all->perpWallDist);
		all->drawStart = -all->lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (all->drawStart < 0)
			all->drawStart = 0;
		all->drawEnd = all->lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(all->drawEnd >= SCREEN_HEIGHT)
			all->drawEnd = SCREEN_HEIGHT - 1;
		
		if (all->side == 0)
			all->wallX = all->player.posY + all->perpWallDist * all->rayDirY;
		else
			all->wallX = all->player.posX + all->perpWallDist * all->rayDirX;
		all->wallX -= floor((all->wallX));

		int texX = (int)(all->wallX * (double)texWidth);
		if (all->side == 0 && all->rayDirX > 0)
			texX = texWidth - texX - 1;
		if (all->side == 1 && all->rayDirY < 0)
			texX = texWidth - texX - 1;
		
		step = 1.0 * 64 / all->lineHeight;
		texPos = (all->drawStart - SCREEN_HEIGHT / 2 + all->lineHeight / 2) * step;
		texY = 0;
		all->i = 0;
		if (all->i < all->drawStart)
		{
			while (all->i < all->drawStart)
			{
				my_mlx_pixel_put(&all->img, all->x, all->i, all->path->celling_colour);
				all->i++;
			}
		}
		while (all->i < all->drawEnd)
		{
			texY = (int)texPos & (64 - 1);
			texPos += step;
			if (all->side == 0) 
			{
				if (all->stepX > 0)
					all->color = all->colors_south[texX][texY]; //S
				else
					all->color = all->colors_north[texX][texY]; //N
			} 
			else
			{
				if (all->stepY < 0)
					all->color = all->colors_west[texX][texY]; //W
				else
					all->color = all->colors_east[texX][texY]; //E
			}
			if (all->side == 1)
				all->color = (all->color >> 1) & 8355711;
			my_mlx_pixel_put(&all->img, all->x, all->i, all->color);
			all->i++;
		}
		while (all->i < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(&all->img, all->x, all->i, all->path->floor_colour);
			all->i++;
		}
		all->x++;
	}
	
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->img.img, 0, 0);
}

void	turn_right(t_all *all)
{
	all->oldDirX = all->player.dirX;
	all->oldPlaneX = all->player.planeX;
	
	all->player.dirX = all->player.dirX * cos(all->rotSpeed) - all->player.dirY * sin(all->rotSpeed);
	all->player.dirY = all->oldDirX * sin(all->rotSpeed) + all->player.dirY * cos(all->rotSpeed);
	all->player.planeX = all->player.planeX * cos(all->rotSpeed) - all->player.planeY * sin(all->rotSpeed);
	all->player.planeY = all->oldPlaneX * sin(all->rotSpeed) + all->player.planeY * cos(all->rotSpeed);
}

void	turn_left(t_all *all)
{
	all->oldDirX = all->player.dirX;
	all->oldPlaneX = all->player.planeX;
	all->player.dirX = all->player.dirX * cos(-all->rotSpeed) - all->player.dirY * sin(-all->rotSpeed);
	all->player.dirY = all->oldDirX * sin(-all->rotSpeed) + all->player.dirY * cos(-all->rotSpeed);
	all->player.planeX = all->player.planeX * cos(-all->rotSpeed) - all->player.planeY * sin(-all->rotSpeed);
	all->player.planeY = all->oldPlaneX * sin(-all->rotSpeed) + all->player.planeY * cos(-all->rotSpeed);
}

void	go_up(t_all *all)
{
	if (all->map[(int)(all->player.posX + all->player.dirX * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		all->player.posX += all->player.dirX * all->moveSpeed;
	if (all->map[(int)(all->player.posX)][(int)(all->player.posY + all->player.dirY * all->moveSpeed)] == 0) 
		all->player.posY += all->player.dirY * all->moveSpeed;
}

void	go_down(t_all *all)
{
	if (all->map[(int)(all->player.posX - all->player.dirX * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		all->player.posX -= all->player.dirX * all->moveSpeed;
	if (all->map[(int)(all->player.posX)][(int)(all->player.posY - all->player.dirY * all->moveSpeed)] == 0) 
		all->player.posY -= all->player.dirY * all->moveSpeed;
}

void	go_left(t_all *all)
{
	if (all->map[(int)(all->player.posX - all->player.dirY * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		all->player.posX -= all->player.dirY * all->moveSpeed;
	if (all->map[(int)(all->player.posX)][(int)(all->player.posY + all->player.dirX * all->moveSpeed)] == 0) 
		all->player.posY += all->player.dirX * all->moveSpeed;
}

void	go_right(t_all *all)
{
	if (all->map[(int)(all->player.posX + all->player.dirY * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		all->player.posX += all->player.dirY * all->moveSpeed;
	if (all->map[(int)(all->player.posX)][(int)(all->player.posY - all->player.dirX * all->moveSpeed)] == 0) 
		all->player.posY -= all->player.dirX * all->moveSpeed;
}



int	key_hook(int keycode, t_all *all)
{
	// double moveSpeed;
	// double rotSpeed;
	// double oldDirX;
	// double oldPlaneX;
	int		x;
	int		y;

	all->rotSpeed = 0.1;
	// all->oldDirX = all->player.dirX;
	// all->oldPlaneX = all->player.planeX;
	all->moveSpeed = 0.1;
	if (all->mini.on % 2 == 0)
	{
		mlx_destroy_image(all->mlx.mlx, all->img_map.img);
	}
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		ft_putstr_fd("Close window\n", 1);
		exit(1);
	}
	if (keycode == 13 || keycode == 126) //w
	{
		go_up(all);
		// if (all->map[(int)(all->player.posX + all->player.dirX * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		// 	all->player.posX += all->player.dirX * all->moveSpeed;
		// if (all->map[(int)(all->player.posX)][(int)(all->player.posY + all->player.dirY * all->moveSpeed)] == 0) 
		// 	all->player.posY += all->player.dirY * all->moveSpeed;
	}
	if (keycode == 1 || keycode == 125) //s
	{
		go_down(all);
		// if (all->map[(int)(all->player.posX - all->player.dirX * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		// 	all->player.posX -= all->player.dirX * all->moveSpeed;
		// if (all->map[(int)(all->player.posX)][(int)(all->player.posY - all->player.dirY * all->moveSpeed)] == 0) 
		// 	all->player.posY -= all->player.dirY * all->moveSpeed;
	}
	if (keycode == 124 /*|| keycode == 2*/) //d = 2
	{
		turn_left(all);
	}
	if (keycode == 123 /*|| keycode == 0*/) //a = 0
	{
		turn_right(all);
	}
	if (keycode == 2) //d
	{
		go_right(all);
		// if (all->map[(int)(all->player.posX + all->player.dirY * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		// 	all->player.posX += all->player.dirY * all->moveSpeed;
		// if (all->map[(int)(all->player.posX)][(int)(all->player.posY - all->player.dirX * all->moveSpeed)] == 0) 
		// 	all->player.posY -= all->player.dirX * all->moveSpeed;
	}
	if (keycode == 0) //a
	{
		go_left(all);
		// if (all->map[(int)(all->player.posX - all->player.dirY * all->moveSpeed)][(int)(all->player.posY)] == 0) 
		// 	all->player.posX -= all->player.dirY * all->moveSpeed;
		// if (all->map[(int)(all->player.posX)][(int)(all->player.posY + all->player.dirX * all->moveSpeed)] == 0) 
		// 	all->player.posY += all->player.dirX * all->moveSpeed;
	}
	mlx_destroy_image(all->mlx.mlx, all->img.img);
	all->img.img = mlx_new_image(all->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	print(all);
	if (keycode == 48)
	{
		all->mini.on++;
	}
	if (all->mini.on % 2 == 0)
	{
		all->img_map.img = mlx_new_image(all->mlx.mlx, all->map_max_width * 10, all->map_max_height * 10);
		all->img_map.addr = mlx_get_data_addr(all->img_map.img, &all->img_map.bits_per_pixel, &all->img_map.line_length, &all->img_map.endian);
		print_mini_map(all);
		print_player(all, 0xfa0000);
		mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->img_map.img, 0, 0);
	}
	return (0);
}

int	mouse_hook(int keycode, t_all *all)
{
	printf("%d\n", keycode);
	return (0);
}

int	mouse_movement(int x, int y, t_all *all)
{	
	if (all->mouse.x == -1)
	{
		all->mouse.x = x;
		all->prev_mouse.x = x;
		all->mouse.y = y;
		all->prev_mouse.y = y;
	}
	else
	{
		all->prev_mouse.x = all->mouse.x;
		all->mouse.x = x;
		all->prev_mouse.y = all->mouse.y;
		all->mouse.y = y;
	}
	printf("%d\n",all->prev_mouse.x);
	printf("%d\n",all->mouse.x);
	if ((all->mouse.x < (all->map_max_width / 2) && all->mouse.x < all->prev_mouse.x))
		turn_right(all);
	if ((all->mouse.x > (all->map_max_width / 2) && all->mouse.x > all->prev_mouse.x))
		turn_left(all);
	return (0);
}

void	raycaster(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	all->mini.on = 1;
	all->mlx.mlx = mlx_init();
	all->mlx.win = mlx_new_window(all->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	all->img.img = mlx_new_image(all->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	all->img_map.img = mlx_new_image(all->mlx.mlx, all->map_max_width * 10, all->map_max_height * 10);
	all->img_map.addr = mlx_get_data_addr(all->img_map.img, &all->img_map.bits_per_pixel, &all->img_map.line_length, &all->img_map.endian);

	print(all);
	int	x1;
	int	y1;

	mlx_mouse_get_pos(all->mlx.win, &x1, &y1);
	printf("%d %d\n", x1, y1);
	mlx_mouse_move(all->mlx.win, x, y);
	mlx_hook(all->mlx.win, 17, 1L << 0, close_win, &all->img);
	mlx_hook(all->mlx.win, 2, 1L << 0, key_hook, all);
	// mlx_mouse_hook(all->mlx.win, mouse_hook, all);
	// mlx_hook(all->mlx.win, 6, 1L << 6, &mouse_movement, all);
	mlx_loop(all->mlx.mlx);
}
