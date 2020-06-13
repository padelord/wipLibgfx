#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "gfx.h"
#include "mlx.h"

typedef struct	s_mouse
{
	int	x;
	int	y;
	t_vec2	pos;
	t_texture	txt;
}				t_mouse;

typedef struct	s_win
{
	void		*ptr;
	int			x;
	int			y;
}				t_win;

typedef	struct	s_core
{
	void	*mlx;
	t_win	win;
	t_img	*img;
	void	*param;
	int		fps;
	t_vec2	size;
	t_vec2	hsize;
	t_mouse	mouse;
	void 	(*free_data)(void**);
	void	*data;
}				t_core;

#define ST_GET 1
#define ST_SET 2
#define ST_DEL 4

void delcore(t_core *core)
{
	mlx_mouse_show(core->mlx, core->win.ptr);
	mlx_destroy_window(core->mlx, core->win.ptr);
}

t_core	*st_core(int mod)
{
	static	t_core	core;

	if (mod == ST_GET)
		return (&core);
	if (mod == ST_DEL)
	{
		delcore(&core);
		return (0);
	}
	return (0);
}

t_core	*st_initcore(t_vec2 size, char *name)
{
	t_core	*core;

	if (!((core = st_core(ST_GET)) && (core->mlx = mlx_init()) &&
		(core->win.ptr = mlx_new_window(core->mlx, size.x, size.y, name))))
		return (0);
	if (!(core->img = init_image(core->mlx, size.x, size.y)))
		return (0);
	core->size = size;
	core->hsize = core->size / 2;
	core->mouse.pos = core->hsize;
	return (core);
}

#define E_TIME 10000
#include <sys/time.h>
void full_img(t_img *img, t_u32 color)
{
	t_u32	*tab;
	t_u32	size;

	tab = img->data;
	size = img->size.x * img->size.y;
	while (size--)
		*tab++ = color;
}

int	draw_curs(void *mlx, void *win, int x, int y)
{
	int	i;

	i = -1;
	while (++i < 20)
	{
		mlx_pixel_put(mlx, win, x + i, y, 0x00BB00);
		mlx_pixel_put(mlx, win, x - i, y, 0x00BB00);
		mlx_pixel_put(mlx, win, x, y + i, 0x00BB00);
		mlx_pixel_put(mlx, win, x, y - i, 0x00BB00);
	}
	return (0);
}

t_u32		ft_abs(int n)
{
	return ((n & 0x80000000) ? (t_u32) -n : n);
}

#define BUT_DIST 100

int		isnear(t_vec2 p1, t_vec2 p2)
{
	t_uvec2	d;

	d = (t_uvec2){ft_abs(p1.x - p2.x), ft_abs(p1.y - p2.y)};
	printf("dist : %dx%d\n", d.x, d.y);
	if (d.x > BUT_DIST || d.y > BUT_DIST)
		return (0);
	if (d.x * d.x + d.y * d.y <= 10000)
		return (1);
	return (0);
}

/*
int	draw_curs(void *mlx, void *win, int x, int y)
{
	t_vec2	i;

	i.x = x - 20;
	i.y = y - 20;
	while (i.x < x + 20)
	{
		mlx_pixel_put(mlx, win, i.x++, y, 0xFFFFFF);
		mlx_pixel_put(mlx, win, x, i.y++, 0xFFFFFF);
	}
}
*/
int	fx_loop(void *param)
{
	t_core		*e;
	static long felapsed;
	static long elapsed;
	struct timeval f0, f1;
	struct timeval t0, t1;

	gettimeofday(&f0, 0);
	gettimeofday(&t0, 0);
	long waiting = ((elapsed < 16666) ? 16666 - elapsed : 0);
	e = (t_core*)param;
	//full_img(e->img, 0xFF0000);
	mlx_put_image_to_window(e->mlx, e->win.ptr, e->img->ptr, 0, 0);

	dprintf(1, "mouse:%d:%d\n",e->mouse.pos.x, e->mouse.pos.y);// e->mouse.x - e->hsize.x, e->mouse.y - e->hsize.y);
	e->mouse.pos += (t_vec2){e->mouse.x, e->mouse.y} - e->hsize;
	//mlx_mouse_move(e->mlx, e->win.ptr, e->hsize.x, e->hsize.y);
	if (isnear(e->mouse.pos, e->hsize))
		draw_curs(e->mlx, e->win.ptr, e->hsize.x, e->hsize.y);
	else
		draw_curs(e->mlx, e->win.ptr, e->mouse.pos.x, e->mouse.pos.y);
	printf("last frame : %ld µs\n", felapsed);
	gettimeofday(&t1, 0);
	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	usleep(waiting);
	gettimeofday(&f1, 0);
	felapsed = (f1.tv_sec-f0.tv_sec)*1000000 + f1.tv_usec-f0.tv_usec;
	return (0);
}

int		fx_errno(int mod, int err)
{
	static int value = 0;

	if (mod & ST_SET)
		value = err;
	if (mod & ST_GET)
		return (value);
	return (0);
}

int		fx_key_hook(int key, void *param)
{
	t_core *e;

	e = (t_core *)param;
	if (key == K_SPC)
		mlx_mouse_move(e->mlx, e->win.ptr, e->hsize.x, e->hsize.y);
	if (key == K_ESC)
		exit((int)st_core(ST_DEL));
	return (0);
}

int		fx_expose(void *param)
{
	t_core *e;

	e = (t_core *)param;
	(void)e;
	dprintf(1, "Coucou\n");
	return (0);
}

int		fx_close_hook(void *param)
{
	t_core	*e;

	e = (t_core *)param;
	delcore(e);
	exit(0);
	return (0);
}

int		fx_mouse_move(int x, int y, void *param)
{
	t_core	*e;

	e = (t_core*)param;
	e->mouse.x = x;
	e->mouse.y = y;
	if (x == e->hsize.x && y == e->hsize.y)
		return (0);
	mlx_mouse_move(e->mlx, e->win.ptr, e->hsize.x, e->hsize.y);
	return (0);
}

void	fx_launch()
{
	t_core	*e;
	int		x;
	int		y;

	e = (t_core*)st_core(ST_GET);
	mlx_get_screen_size(e->mlx, &x, &y);
	dprintf(1, "size of screen : %dx%d\n", x, y);
	mlx_expose_hook(e->win.ptr, fx_expose, e);
	mlx_key_hook(e->win.ptr, fx_key_hook, e);
	mlx_hook(e->win.ptr, 6, (1U << 6), fx_mouse_move, e);
	mlx_hook(e->win.ptr, 17, (1L << 17), fx_close_hook, e);
	mlx_loop_hook(e->mlx, fx_loop, e);
	//mlx_mouse_hide(e->mlx, e->win.ptr);
	mlx_mouse_move(e->mlx, e->win.ptr, e->mouse.pos.x, e->mouse.pos.y);
	mlx_loop(e->mlx);
}

int	vec_isequal(t_vec2 a, t_vec2 b)
{
	return (a.x == b.x && a.y == b.y);
}

int	vec_isupper(t_vec2 a, t_vec2 b)
{
	return (a.x > b.x && a.y > b.y);
}

int	vec_islower(t_vec2 a, t_vec2 b)
{
	return (a.x < b.x && a.y < b.y);
}

int	main(int ac, char **av)
{
	t_vec2	a;
	t_vec2	b;

	a = (t_vec2){1, 2};
	b = (t_vec2){2, 3};
	if (vec_islower(a, b))
		dprintf(1,"C'est moins\n");
	if (vec_isupper(a, b))
		dprintf(1,"C'est plus\n");
	if (vec_isequal(a, b))
		dprintf(1,"C'est pareil\n");
	if (st_initcore((t_vec2){1080, 720}, "blabla"))
		fx_launch();
	else
		printf("error\n");
	printf("%s\n", av[ac - 1]);
	return (0);
}
/*
#define SUPTIME 100

int	ft_wischar(char *buffer, char c, int size)
{
	int	i;

	i = 0;
	while (buffer[i] != c && buffer[i] && i < size)
		++i;
	return ((buffer[i] && i < size) ? i : -1);
}

typedef struct s_fps
{
	int	p;
	int	c;
	int	f;
	int	fps;
}				t_fps;

int	fx_fps()
{
	t_core	*e;
	static	t_fps data = (t_fps){0, 0, 0, 0};
	char		buff[SUPTIME + 1];
	int			size;
	int			fd;

	if ((fd = open("/proc/uptime", O_RDONLY)) == -1)
		return (-1);
	size = (int)read(fd, buff, SUPTIME);
	buff[size] = 0;
	if ((size = ft_wischar(buff, '.', size)) != -1)
		buff[size] = 0;
	else
		return (((close(fd)) == -1) ? -2 : -1);
	data.p = data.c;
	if ((data.c = ft_atoi(buff)) != data.p)
	{
		data.fps = data.f;
		data.f = 0;
	}
	e = ft_core();
	close(fd);
	++data.f;
	e->fps = data.fps;
	return (0);
}

int	fx_initcore(char *title, int x, int y)
{
	t_core	*e;

	e = (t_core*)fx_getcore();
	if (!(e->mlx = mlx_init()))
		return (-1);
	if (!(e->win = mlx_new_window(e->mlx, x, y, title)))
		return (-2);
	e->fps = 0;
	return (0);
}
*/
