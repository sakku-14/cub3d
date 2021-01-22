#define TRUE	0
#define FALSE	1

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#define IMG_WIDTH	50
#define IMG_HEIGHT	50

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_release	3
#define X_EVENT_KEY_EXIT	17

#define KEY_ESC	53
#define KEY_LEFT	123
#define KEY_RIGHT	124
#define KEY_UP		126
#define KEY_DOWN	125

typedef struct	s_param
{
	int		x;
	int		y;
}				t_param;

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_window
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}				t_window;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win;
	t_param	param;
	t_img	img;
	t_window	window;
}				t_mlx;

