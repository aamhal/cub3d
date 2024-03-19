/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:30:29 by aamhal            #+#    #+#             */
/*   Updated: 2024/03/19 13:04:46 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	creat_window(t_direct *direct)
{
	t_mlx	mlx;

	mlx.drct = direct;
	mlx.play = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	mlx.t = ft_calloc(1, sizeof(t_textures));
	if (check_texters(direct) == -1)
		exit_func(&mlx);
	make_textures(mlx.t, direct);
	mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", 0);
	creat_player(mlx);
	mlx_loop_hook(mlx.mlx, &map_loop, &mlx);
	mlx_key_hook(mlx.mlx, &mlx_key, &mlx);
	mlx_loop(mlx.mlx);
	exit_func(&mlx);
}

void	creat_player(t_mlx mlx)
{
	mlx.play->pos_x = mlx.drct->p_x * TS - TS / 2;
	mlx.play->pos_y = mlx.drct->p_y * TS - TS / 2;
	mlx.play->radfov = (FOV * M_PI) / 180;
	if (mlx.drct->d == 'N')
		mlx.play->angle = (3 * M_PI) / 2;
	else if (mlx.drct->d == 'S')
		mlx.play->angle = M_PI / 2;
	else if (mlx.drct->d == 'W')
		mlx.play->angle = 0;
	else
		mlx.play->angle = M_PI;
}

void	map_loop(void *m)
{
	t_mlx	*mlx;

	mlx = m;
	mlx_delete_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	calculate_move(mlx, 0, 0);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
	cast_rays(mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= HEIGHT)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}
