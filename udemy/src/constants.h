#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

#define FALSE	0
#define TRUE	1
#define ERROR	-1
#define STDERR	2
#define PI		3.1415926535

#define TILE_SIZE		64
#define MINIMAP_SCALE_FACTOR	4
#define MAP_NUM_ROWS	13
#define MAP_NUM_COLS	20

#define WIN_WIDTH	(MAP_NUM_COLS * TILE_SIZE)
#define WIN_HEIGHT	(MAP_NUM_ROWS * TILE_SIZE)

#define TEXTURE_WIDTH	64
#define TEXTURE_HEIGHT	64

#define FOV_ANGLE	(60 * (M_PI / 180))

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define X_EVENT_BTN_PRESS	4

#define KEY_ESC		53
#define KEY_LEFT	123
#define KEY_RIGHT	124
#define KEY_UP		126
#define KEY_DOWN	125
#define KEY_A	0
#define KEY_D	2
#define KEY_W	13
#define KEY_S	1

typedef struct	s_player
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	float	player_x;
	float	player_y;
	int		width;
	int		height;
	float	rotation_angle;
	int		turn_direction;
	int		walk_direction;
	int		side_direction;
	float	walk_speed;
	float	turn_speed;
}				t_player;

typedef struct	s_line
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}				t_line;


typedef struct	s_window
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	float	perp_distance;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		distance_from_top;
	int		texture_offset_x;
	int		texture_offset_x_rev;
	int		texture_offset_y;
}				t_window;

typedef struct	s_map
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		tile_x;
	int		tile_y;
}				t_map;

typedef struct	s_rays
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
	int		wall_hit_content;
}				t_rays;

typedef struct	s_tex
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}				t_tex;

typedef	struct	s_sprites
{
	float	sprite_x;
	float	sprite_y;
	int		visible;
	float	distance;
	float	angle_from_player;
	float	perp_distance;
	float	distance_proj_plane;
	float	projected_sprite_height;
	int		sprite_strip_height;
	int		sprite_top_pixel;
	int		sprite_bottom_pixel;
	int		distance_from_top;
	int		texture_offset_x;
	int		texture_offset_y;
}				t_sprites;

typedef struct	s_conf
{
	int		win_w;
	int		win_h;
	int		win_max_w;
	int		win_max_h;
	char	*path_no;
	char	*path_so;
	char	*path_ea;
	char	*path_we;
	char	*path_sp;
	int		floor_colors[3];
	int		floor_c;
	int		ceil_colors[3];
	int		ceil_c;
	int		cub_flag[9];
	char	*map_str;
	char	**map;
	int		map_y;
	int		map_x;
	float		pl_y;
	float		pl_x;
	int		rays_free_flag;
}				t_conf;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_window	window;
	t_map		map;
	t_rays		*rays;
	t_sprites	*sprite;
	t_conf		conf;
	int			sprite_num;
	t_tex		tex[5];
}				t_mlx;
