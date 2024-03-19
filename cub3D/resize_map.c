/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:38:06 by aamhal            #+#    #+#             */
/*   Updated: 2024/03/16 14:15:45 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_resize(char **map)
{
	int		i;
	size_t	len;

	i = 0;
	len = longest_row(map);
	while (map[i])
	{
		if (ft_strlen(map[i]) < len)
			map[i] = resize_row(map[i], len - ft_strlen(map[i]));
		else
			map[i] = ft_strjoin(map[i], " ");
		i++;
	}
	return (map);
}

int	longest_row(char **map)
{
	int		i;
	size_t	len;

	i = 1;
	len = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > len)
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

char	*resize_row(char *p, int i)
{
	while (i >= 0)
	{
		p = ft_strjoin (p, " ");
		i--;
	}
	return (p);
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TS);
	y_m = floor (y / TS);
	if ((y >= HEIGHT || x >= WIDTH || (y_m >= mlx->drct->height || \
	x_m >= mlx->drct->width)))
		return (0);
	if (mlx->drct->map[y_m] && x_m <= (int)ft_strlen(mlx->drct->map[y_m]))
		if (mlx->drct->map[y_m][x_m] == '1')
			return (0);
	return (1);
}
