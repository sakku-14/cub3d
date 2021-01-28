#define FALSE	0
#define TRUE	1

#define TILE_SIZE		64
#define MINIMAP_SCALE_FACTOR	4
#define MAP_NUM_ROWS	13
#define MAP_NUM_COLS	20

#define WIN_WIDTH	(MAP_NUM_COLS * TILE_SIZE)
#define WIN_HEIGHT	(MAP_NUM_ROWS * TILE_SIZE)

#define FOV_ANGLE	(60 * (M_PI / 180))
#define NUM_RAYS	1280

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

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_window	window;
	t_map		map;
	t_rays		rays[NUM_RAYS];
	t_tex		tex[5];
}				t_mlx;

