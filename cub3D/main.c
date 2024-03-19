/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:50:32 by aamhal            #+#    #+#             */
/*   Updated: 2024/03/19 13:05:17 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void v()
{
	system("leaks cub3d");
}


	

int	main(int ac, char **av)
{
	// atexit(v);
	t_direct *direct;
	
	if (ac != 2)
		exit(1);
	direct = ft_calloc(sizeof(t_direct), 1);
	parcing(av[1], &direct);
	direct->east = textures_parc(direct->east);
	direct->west = textures_parc(direct->west);
	direct->north = textures_parc(direct->north);
	direct->south = textures_parc(direct->south);
	direct->c = textures_parc(direct->c);
	direct->f = textures_parc(direct->f);
	creat_window(direct);
	return (0);
}
