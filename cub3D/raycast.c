/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:27:41 by akaabi            #+#    #+#             */
/*   Updated: 2024/03/19 13:03:09 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dir_check(float angle, float *tmp, float *move, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*tmp += TS;
			return (0);
		}
		*move *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < (3 * M_PI) / 2))
		{
			*tmp += TS;
			return (0);
		}
		*move *= -1;
	}
	return (1);
}

int	circle_check(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

float	h_intersection(t_mlx *mlx, float angl)
{
	float	h_x;
	float	h_y;
	float	x_move;
	float	y_move;
	int		check;

	y_move = TS;
	x_move = TS / tan(angl);
	h_y = floor(mlx->play->pos_y / TS) * TS;
	check = dir_check(angl, &h_y, &y_move, 1);
	h_x = mlx->play->pos_x + (h_y - mlx->play->pos_y) / tan(angl);
	if ((circle_check(angl, 'y') && x_move > 0) || \
		(!circle_check(angl, 'y') && x_move < 0))
		x_move *= -1;
	while (wall_hit(h_x, h_y - check, mlx))
	{
		h_x += x_move;
		h_y += y_move;
	}
	mlx->ray->h_x = h_x;
	mlx->ray->h_y = h_y;
	return (sqrt(pow(h_x - mlx->play->pos_x, 2) + \
	pow(h_y - mlx->play->pos_y, 2)));
}

float	v_intersectiom(t_mlx *mlx, float angl)
{
	float	v_x;
	float	v_y;
	float	x_move;
	float	y_move;
	int		check;

	x_move = TS;
	y_move = TS * tan(angl);
	v_x = floor(mlx->play->pos_x / TS) * TS;
	check = dir_check(angl, &v_x, &x_move, 0);
	v_y = mlx->play->pos_y + (v_x - mlx->play->pos_x) * tan(angl);
	if ((circle_check(angl, 'x') && y_move < 0) || \
		(!circle_check(angl, 'x') && y_move > 0))
		y_move *= -1;
	while (wall_hit(v_x - check, v_y, mlx))
	{
		v_x += x_move;
		v_y += y_move;
	}
	mlx->ray->v_x = v_x;
	mlx->ray->v_y = v_y;
	return (sqrt(pow(v_x - mlx->play->pos_x, 2) + \
	pow(v_y - mlx->play->pos_y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_angle = mlx->play->angle - (mlx->play->radfov / 2);
	while (ray < WIDTH)
	{
		mlx->ray->flag = 0;
		h_inter = h_intersection(mlx, norm_angle(mlx->ray->ray_angle));
		v_inter = v_intersectiom(mlx, norm_angle(mlx->ray->ray_angle));
		if (v_inter <= h_inter)
			mlx->ray->wall_distance = v_inter;
		else
		{
			mlx->ray->wall_distance = h_inter;
			mlx->ray->flag = 1;
		}
		wall_render(mlx, ray);
		ray++;
		mlx->ray->ray_angle += (mlx->play->radfov / WIDTH);
	}
}
