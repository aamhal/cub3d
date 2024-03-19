/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:37:25 by akaabi            #+#    #+#             */
/*   Updated: 2024/03/19 13:01:22 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	rgb_to_int(mlx->drct, mlx->drct->f);
	while (i < HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, \
		rgba(mlx->drct->r, mlx->drct->g, mlx->drct->b, 100));
	i = 0;
	rgb_to_int(mlx->drct, mlx->drct->c);
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, \
		rgba(mlx->drct->r, mlx->drct->g, mlx->drct->b, 100));
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = norm_angle(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2 \
		&& mlx->ray->ray_angle < (3 * M_PI) / 2)
			return (mlx->t->ea);
		else
			return (mlx->t->we);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->t->so);
		else
			return (mlx->t->no);
	}
}

double	get_x_o(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_o;

	if (mlx->ray->flag == 1)
		x_o = (int)fmodf((mlx->ray->h_x * \
		(texture->width / TS)), texture->width);
	else
		x_o = (int)fmodf((mlx->ray->v_y * \
		(texture->width / TS)), texture->width);
	return (x_o);
}

void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(mlx, mlx->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, mlx);
	if (x_o < 0)
		x_o = 0;
	y_o = (t_pix - (HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, reverse_bytes \
		(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	wall_render(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pixel;
	double	t_pixel;
	double	distancetoprojectplane;

	distancetoprojectplane = (WIDTH / 2) / tan(mlx->play->radfov / 2);
	mlx->ray->wall_distance *= \
	cos(norm_angle(mlx->ray->ray_angle - mlx->play->angle));
	wall_h = (TS / mlx->ray->wall_distance) * distancetoprojectplane;
	b_pixel = (HEIGHT / 2) + (wall_h / 2);
	t_pixel = (HEIGHT / 2) - (wall_h / 2);
	if (b_pixel > HEIGHT)
		b_pixel = HEIGHT;
	if (t_pixel < 0)
		t_pixel = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pixel, b_pixel, wall_h);
	draw_floor_ceiling(mlx, ray, t_pixel, b_pixel);
}
