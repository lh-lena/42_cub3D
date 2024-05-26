/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:09:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/25 14:27:06 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include "libft/libft.h"

# define H 900
# define W 1300
# define HALF_W	W / 2
# define HALF_H	H / 2
# define TILE_SIZE 64
# define PLAYER_SIZE 8
# define PI 3.1415926535 //65358979323846
# define FOV 60
# define FOV_R PI / 3
# define FOV_ANGELS 60 * (PI / 180.0)
# define CASTED_RAYS 320  //amount of rays in FOV
# define STEP_ANGLE FOV_R / CASTED_RAYS
# define MAX_DEPTH H
# define HFOV FOV / 2
# define PL_STEP 4
# define SCALE (W / 2) / CASTED_RAYS
# define MINIMAP_SCALE 0.2


/**
 * 
 * 		3Pi/2
 * 		 270
 * 
 *  Pi			0
 * 180			0
 * 				
 * 		Pi/2
 *		 90
 * 
*/

typedef struct s_map_utils
{
	int	row;
	int	col;
	char cur_char;
	char *cur_row;
	char *row_on_top;
	char *row_on_btm;
	int cur_row_len;
	int top_row_len;
	int btm_row_len;
}	t_map_utils;


/*!
 *	@struct				s_image
 *	@brief				Represents an image in the MiniLibX graphics library
 *	@param mlx_img		A pointer to the mlx image structure
 *	@param addr			A pointer to the image buffer
 *	@param bpp			The number of bits per pixel
 *	@param line_length	The length of a line in bytes
 *	@param endian		The endian of the image data
 */

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_line
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	color;
}	t_line;

/**
 * @struct					s_ray
 * @brief					Represents a ray
 * @param	wall_hit_x		X-coordinate of the wall hit
 * @param	wall_hit_y		Y-coordinate of the wall hit

*/

typedef struct s_ray
{
	int		vert_hit;
	float	ray_angle;
	float	distance;
	int		wall_height;
	int		ray_count;
	int		wall_hit_x;
	int		wall_hit_y;
	int		up;
	int		right;
	int		left;
	int		down;

	// float	ray_dir_x;
	// float	ray_dir_y;


	// float	ray_cos;
	// float	ray_sin;
}	t_ray;


/**
 * @struct			s_map
 * @brief			Represents a map with player coordinates and view direction
 * @param	px		X-coordinate of the player
 * @param	py		Y-coordinate of the player
 * @param	pdx		delta Y
 * @param	pdx		delta X
 * @param	pa		Angle of the player view's direction
 * @param	view	Direction the player is facing (N, S, E, W)
 * @param	map		2D array representing the map
*/

typedef struct s_player
{
	int		player_fov;
	float	px; // in pixels
	float	py;
	// float	pdy;
	// float	pdx;
	float	pa;
	float	pa_rad;
	float	rotation_speed;
}	t_player;

typedef struct s_map
{
	char		*str;
	char		view;
	char		**map;
	int			px;
	int			py;
}	t_map;

/**
 *	@struct		s_elem
 *	@brief		Represents an element with directional information and 
 				color properties
 *	@param so	Represents the direction South
 *	@param no	Represents the direction North
 *	@param ea	Represents the direction East
 *	@param we	Represents the direction West
 *	@param rgb_f	Array representing the foreground color
 *	@param rgb_c	Array representing the ceiling color
 */

typedef struct s_elem
{
	int		rgb_f[3];
	int		rgb_c[3];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_elem;

/*!
 *	@struct			s_data
 *	@brief			Represents the main data structure containing various
					elements for handling the application state
 *	@param mlx_ptr	A pointer to the main mlx (MiniLibX) structure
 *	@param win_ptr	A pointer to the window structure
 *	@param name		A pointer to the name of the window
 *	@param fd		The file descriptor for file operations
 *	@param arr_file	An array containing lines read from a file
 *	@param rows		The number of rows in the game map
 *	@param lines		The total number of lines read from the file
 *	@param offset		An offset for shifting elements in the array
 *	@param img		An instance of the t_image struct representing an image
 *	@param map		A pointer to the t_map struct containing map data
 *	@param elem		A pointer to the t_elem struct containing element data
 */

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*name;
	int			fd;
	char		**arr_file;
	int			rows;
	int			cols;
	int			lines;
	int			offset;
	int			degrees;
	t_image		img;
	t_map		*map;
	t_elem		*elem;
	t_ray		*ray;
	t_player	*player;
}	t_data;

/* allowed function:
 open, close, read, write,
 printf, malloc, free, perror,
 strerror, exit
*/

// init data & win

void	data_init(t_data *data);
void	window_init(t_data *data);


int		game_map_dup(t_data *data, char **arr);
void	draw_line(t_line *line, t_data *data);
void	draw_line_other(t_line *line, t_data *data);
void	mini_map(t_data *data);
void	draw_mini_map(t_data *data, int map_y, int map_x);
void	draw_player(t_data *data, int map_y, int map_x);
float	degrees_to_radians(int degrees);
int		get_degree(char view);
int		fix_angle(int a);
void	draw_player_dir(t_data *data, float target_x, float target_y);

int		validate_map(char **map, int rows);

// read file
int		check_filename(char *str, char *extention);
int		file_line(char *file, t_data	*data);
int		read_file(char *file, t_data	*data);
int		copy_file(char *file, t_data *data);
int		validate_player(t_data *data, char **map, int rows);
int		validate_file_content(char *file, t_data *data);
int		parce_file(t_data *data);

int		copy_data(t_data *data, char *s);
int		fill_struct_elem(t_data *data, char **s);
int		copy_texture(t_data *data, char **s, char **texture);
int		copy_c_color(t_data *data, char **s);
int		copy_f_color(t_data *data, char **s);
int		validate_elem(t_elem *elem);

int		cross(t_data *data);
int		keypress(int keysym, t_data *data);
// int		mouse(int button, int x, int y, t_data *data);
void	display_controls(void);
void	move_player(t_data *data, float target_x, float target_y);
void	rotate_player(t_data *data, t_player *player, int keysym);
int		has_wall_at(t_data *data, float x, float y);

// draw game
void	game_init(t_data *data);
void	game(t_data *data);
void	draw_game(int x, int y, t_data *data);
void	ft_pixel_put(t_image *img, int x, int y, int color);
int		ft_rgb(int r, int g, int b);
// void	draw_line(t_data *data, t_line *line, int color);

// raycalsting
void	cast_ray(t_data *data, t_player *player, t_ray *ray);
void	cast_all_rays(t_data *data, t_player *player, t_ray *ray);
void	update_ray(t_ray *ray);
float	normilize_angle(float angle);
void	init_struct_ray(t_ray *ray, t_player *player);
float	get_distance(float px, float py, float hit_x, float hit_y);
float	wall_strip_height(t_ray *ray);
float	distance_proj_plane(void);


void	malloc_error(void);
void	clean_up_data(t_data *data);
void	free_elem(t_elem *elem);
void	free_arr_int(int **arr, int size);
int		print_error(char *s);

// utils
void	print_arr(char **arr);
size_t	ft_arrlen(char **arr);
size_t	ft_arrsize(char	**arr);
int		is_whitespace(char c);
int		is_whitespace_str(char *str);
int		ft_isspace(int c);
int		ft_isdigit_str(char *s);
void	ft_free(char **str);
void	ft_free_arr(char **arr);
int		count_elem(char *s, char c);

#endif