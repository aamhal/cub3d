/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:43:42 by aamhal            #+#    #+#             */
/*   Updated: 2024/03/19 13:00:22 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "MLX/MLX42.h"

# define TS 32
# define PS 5
# define RS 0.045
# define FOV 60
# define WIDTH 1900
# define HEIGHT 1000

typedef struct l_list
{
	struct l_list	*next;
	char			*line;
}	t_list;

typedef struct l_direct
{
	char	d;
	char	**map;
	int		p_x;
	int		p_y;
	int		width;
	int		height;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*f;
	char	*c;
	int		r;
	int		g;
	int		b;
}	t_direct;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	double	angle;
	float	radfov;
	int		rotation;
	int		r_flag;
	int		lr_flag;
	int		ud_flag;
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	int		flag;
	double	wall_distance;
	int		index;
	int		v_x;
	int		v_y;
	int		h_x;
	int		h_y;
}	t_ray;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_textures;

typedef struct s_mlx
{
	t_textures	*t;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_ray		*ray;
	t_direct	*drct;
	t_player	*play;
}	t_mlx;

//parcing
void	parcing(char *av, t_direct **d);
int		check_extension(char *av);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(char *p);
t_list	*fill_list(t_list *map, char *av);
void	print_nodes2(t_list *s);
t_list	*find_map(t_list **list);
char	**fill_map(t_list **list);
int		find_line(char *p);
int		left_wall(char **map);
int		right_wall(char **map);
int		first_wall(char *map);
int		last_wall(char **map);
int		check_character(char **map);
int		if_map_cover(char **map, int i, int j);
int		map_iterate(char **map);
int		longest_row(char **map);
char	**map_resize(char **map);
char	*resize_row(char *p, int i);
int		direction_parc(char **dir);
char	**make_dir(t_list **list);
int		counting_dir(char **dir);
int		check_is_empty(char *p);
int		fill_no(t_direct **direct, char **dir);
int		fill_so(t_direct **direct, char **dir);
int		fill_we(t_direct **direct, char **dir);
int		fill_ea(t_direct **direct, char **dir);
int		fill_c(t_direct **direct, char **dir);
int		fill_f(t_direct **direct, char **dir);
void	free_array(char **p);
void	free_list(t_list **list);
void	ft_error(t_direct **direct, char **dir, t_list **list);
int		map_iterate_norm(char c, int *count);
void	fill_direct(t_direct **direct);
char	*textures_parc(char *p);
int		check_texters(t_direct *dir);
void	make_textures(t_textures *t, t_direct *dir);

//execution

void	creat_window(t_direct *direct);
void	creat_player(t_mlx mlx);
void	map_loop(void *m);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	exit_func(t_mlx *mlx);

///

void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx); // release the key
void	mlx_key(mlx_key_data_t keydata, void *ml); // key press
void	move_player(t_mlx *mlx, float x, float y);
void	calculate_move(t_mlx *mlx, float x, float y);
float	norm_angle(float angle);
void	rgb_to_int(t_direct *direct, char *p);
void	cast_rays(t_mlx *mlx);
void	wall_render(t_mlx *mlx, int ray);
int		wall_hit(float x, float y, t_mlx *mlx);
int		rgba(int r, int g, int b, int a);
float	norm_angle(float angle);
int		reverse_bytes(int c);
int		dir_check(float angle, float *tmp, float *move, int is_horizon);

void	draw_2d_map(t_mlx *mlx);
void	draw_player(t_mlx *mlx, int x_p, int y_p, int color);
void	check_newline(int r, char **map);

#endif