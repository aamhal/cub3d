/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:02:51 by aamhal            #+#    #+#             */
/*   Updated: 2024/03/19 13:02:32 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_direct(t_direct **direct)
{
	int	i;
	int	j;

	i = 0;
	while ((*direct)->map[i])
	{
		j = 0;
		while ((*direct)->map[i][j])
		{
			if ((*direct)->map[i][j] == 'N' || (*direct)->map[i][j] == 'W' || \
			(*direct)->map[i][j] == 'S' || (*direct)->map[i][j] == 'E')
			{
				(*direct)->p_x = j + 1;
				(*direct)->p_y = i + 1;
				(*direct)->d = (*direct)->map[i][j];
				break ;
			}
			j++;
		}
		i++;
	}
	(*direct)->width = j;
	(*direct)->height = i;
}

char	*textures_parc(char *p)
{
	int		len;
	int		i;
	char	*tmp;

	len = ft_strlen(p);
	while (p[len] == ' ')
		len--;
	i = len;
	while (p[len] != ' ')
		len--;
	tmp = ft_substr(p, len + 1, i - len + 1);
	free(p);
	return (tmp);
}

int	check_texters(t_direct *dir)
{
	mlx_texture_t	*t;

	t = mlx_load_png(dir->east);
	if (!t)
		return (-1);
	mlx_delete_texture(t);
	t = mlx_load_png(dir->west);
	if (!t)
		return (-1);
	mlx_delete_texture(t);
	t = mlx_load_png(dir->east);
	if (!t)
		return (-1);
	mlx_delete_texture(t);
	t = mlx_load_png(dir->north);
	if (!t)
		return (-1);
	mlx_delete_texture(t);
	t = mlx_load_png(dir->south);
	if (!t)
		return (-1);
	mlx_delete_texture(t);
	return (0);
}

void	make_textures(t_textures *t, t_direct *dir)
{
	t->ea = mlx_load_png(dir->east);
	t->we = mlx_load_png(dir->west);
	t->no = mlx_load_png(dir->north);
	t->so = mlx_load_png(dir->south);
}

void	rgb_to_int(t_direct *direct, char *p)
{
	char	**rgb;

	rgb = ft_split(p, ',');
	direct->r = ft_atoi(rgb[0]);
	direct->g = ft_atoi(rgb[1]);
	direct->b = ft_atoi(rgb[2]);
	free_array(rgb);
}
