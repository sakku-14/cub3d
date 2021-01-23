#define FALSE	0
#define TRUE	1

#define	PI	3.14159265
#define	TWO_PI	6.28318530

#define TILE_SIZE		64
#define MINIMAP_SCALE_FACTOR	1
#define MAP_NUM_ROWS	13
#define MAP_NUM_COLS	20

#define WIN_WIDTH	(MAP_NUM_COLS * TILE_SIZE)
#define WIN_HEIGHT	(MAP_NUM_ROWS * TILE_SIZE)

#define FOV_ANGLE	(60 * (PI / 180))

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_release	3
#define X_EVENT_KEY_EXIT	17
#define X_EVENT_BTN_PRESS	4

#define KEY_ESC		53
#define KEY_LEFT	123
#define KEY_RIGHT	124
#define KEY_UP		126
#define KEY_DOWN	125

typedef struct	s_player
{
	void	*player_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	float	player_x;
	float	player_y;
	int	width;
	int	height;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}				t_player;

typedef struct	s_window
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
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


typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_window	window;
	t_map		map;
}				t_mlx;

