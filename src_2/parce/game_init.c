/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/21 16:31:10 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

void	game_init(t_data *data)
{
	data->degrees = get_degree(data->map->view);
	printf("degree: %i\n", data->degrees);
	data->player->pa_rad = degrees_to_radians(get_degree(data->map->view));
	data->player->pdy = -sin(data->player->pa_rad);
	data->player->pdx = cos(data->player->pa_rad);
	data->player->px = data->map->px * CELLSIZE + CELLSIZE / 2;
	data->player->py = data->map->py * CELLSIZE + CELLSIZE / 2;
	// printf("data->player->py: %f, data->player->px :%f\n", data->player->py, data->player->px);

	// if (data->degrees == 90)
	// {
	// 	write(1, "here1\n", 6);
	// 	data->map->pdy = sin(data->map->pa_rad);
	// 	data->map->pdx = -cos(data->map->pa_rad);
	// }
	// else if (data->degrees == 270)
	// {
	// 	write(1, "here2\n", 6);
	// 	data->map->pdy = sin(data->map->pa_rad);
	// 	data->map->pdx = -cos(data->map->pa_rad);
	// }
	// else
	// {
	// 	write(1, "here3\n", 6);
	// 	data->map->pdy = sin(data->map->pa_rad);
	// 	data->map->pdx = cos(data->map->pa_rad);
	// }
	init_struct_ray(data);
}

void	init_struct_ray(t_data *data)
{
	data->ray->x = 0;
	data->ray->y = 0;
	// data->ray->ray_angle = data->player->pa_rad - (FOV_R / 2);
}

void	game(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// my_print(data, NULL);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (x < W)
	{
		y = 0;
		while (y < H)
		{
			draw_game(x, y, data);
			y++;
		}
		x++;
	}
	// raycasting(data);
	mini_map(data);
	draw_player(data);
	cast_rays(data, data->player, data->ray);
	// draw_rays_2d(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 0, 0);
}

void	draw_game(int x, int y, t_data *data)
{
    ft_pixel_put(&data->img, x, y, ft_rgb(235, 206, 250));
}

void	ft_pixel_put(t_image *img, int x, int y, int color)
{
	int	pixel;

	pixel = (img->line_length * y) + (x * (img->bpp / 8));
	*((unsigned int *)(pixel + img->addr)) = color;
}

int	ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
