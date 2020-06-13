/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:35:05 by crenaudi          #+#    #+#             */
/*   Updated: 2020/06/13 21:15:00 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H

# define GFX_H

# include <stdbool.h>
# include <math.h>
# include "mlx.h"
# include "ft_keymap.h"
# include "libft.h"

# define SUCCESS		0
# define ERROR			-1
# define R_TX_MALC		0x0000001U
# define R_TX_SIZE		0x0000002U
# define R_TX_FILE		0x0000004U
# define C_TRANSP		0x980088
# define SPRIT_ISANIM	1U
# define SPRIT_ISINCD	2U
# define ANIM_SPEED		15

typedef unsigned char		t_u16;
typedef unsigned int		t_u32;
typedef char				t_16;
typedef int					t_32;
typedef long				t_64;
typedef	t_u32				t_uvec2 __attribute__((ext_vector_type(2))); 
typedef int					t_vec2 __attribute__((ext_vector_type(2)));
typedef int					t_vec3 __attribute__((ext_vector_type(3)));
typedef int					t_vec4 __attribute__((ext_vector_type(4)));
typedef float				t_vecf2 __attribute__((ext_vector_type(2)));
typedef float				t_vecf3 __attribute__((ext_vector_type(3)));
typedef float				t_vecf4 __attribute__((ext_vector_type(4)));
typedef double				t_vecd2 __attribute__((ext_vector_type(2)));
typedef double				t_vecd3 __attribute__((ext_vector_type(3)));
typedef double				t_vecd4 __attribute__((ext_vector_type(4)));
typedef t_vecf3				t_point;
typedef struct s_listpoint	t_listpoint;
typedef t_vecf4				t_q;
typedef struct s_cam2d		t_cam2d;
typedef struct s_cam3d		t_cam3d;
typedef struct s_bresenham	t_bresenham;
typedef struct s_texture	t_texture;
typedef struct s_sprite		t_sprite;
typedef	struct s_img		t_img;
typedef struct s_color		t_color;
typedef struct s_hsl		t_hsl;
typedef struct s_win		t_win;
typedef union u_rgb			t_rgb;

struct					s_cam2d
{
	float				fov;
	float				half_fov;
	float				speed_move;
	float				speed_angle;
	t_vecf2				dir;
};

struct					s_cam3d
{
	t_vecf3				right;
	t_vecf3				up;
	t_vecf3				forward;
	t_vecf3				from;
	float				fov;
};

struct					s_listpoint
{
	float				x;
	float				y;
	float				z;
	struct s_listpoint	*next;
};

struct					s_texture
{
	t_u32				**frames;
	t_u32				*src;
	t_vec2				size;
	int					nframes;
};

struct					s_sprite
{
	t_texture			*tx;
	t_u32				mod;
	t_vec2				pos;
	int					cframe;
	int					cd;
	int					tof;
};

struct					s_img
{
	void				*ptr;
	t_u32				*data;
	int					bpp;
	int					sl;
	int					endian;
	t_vec2				size;
};

struct					s_color
{
	int					r;
	int					g;
	int					b;
	int					color;
};

struct					s_hsl
{
	int					h;
	int					s;
	int					l;
};

union					u_rgb
{
	unsigned char		rgba[4];
	unsigned int		full;
};

struct					s_bresenham
{
	t_vecf3				tmp;
	t_vecf2				p1;
	t_vecf2				p2;
	t_vecf2				dir;
	t_vecf2				sens;
	float				t;
	t_color				c1;
	t_color				c2;
	t_img				*img;
	int					w;
	int					h;
	float				scl;
	t_vecf2				tr;
	float				bert;
};



/*
** color :
** hsl2rgb ou hsltorgb? dans le .c c'est écrit hsltorgb
*/

float					float_min(float *n);
float					float_max(float *n);
t_vecf3					rgb2hsl(float r, float g, float b);
int						hsl2rgb(float hue, float sat, float lum);
t_color					init_color(int color);
int						lerp_color(t_color s, t_color e, float t);
int						lerp_non_init_color(int a, int b, float t);

/*
** Maths : il manque pas les quaternions? (add/mult/equal...)
** Edit: j'ai trouvé quaternion_equal au milieu des caméras ;)
** mais pas les autres...
*/

float					vecf2_dist(t_vecf2 v2);
t_point					normalize(t_point v);
float					dot_product(t_vecf3 a, t_vecf3 b);
t_point					cross_product(t_vecf3 a, t_vecf3 b);
float					deg2rad(float d);
float					rad2deg(float r);
void					rotate_x(t_point *p, float a);
void					rotate_y(t_point *p, float a);
void					rotate_z(t_point *p, float a);
void					scale(t_point *p, float e);
float					spherical_theta(t_point v);
float					spherical_phi(t_point v);
t_point					to_vec_spherical(t_point v);
void					spherical_perspective(t_point v, t_point *p);
bool					quaternion_equal(t_q *q1, t_q *q2);

/*
** Struct_cam :
*/

t_cam2d					init_cam2d();
void					clean_cam2d(t_cam2d *c);
t_cam3d					init_cam3d(t_vecf3 from, t_vecf3 to, t_vecf3 tmp);
void					matrice_cam3d(t_cam3d *c, t_vecf3 from, t_vecf3 to,
		t_vecf3 tmp);
void					clean_cam3d(t_cam3d *c);

/*
** Struct_img :
** apply_tx_scaled n'est pas codé, on a dit qu'on n'en avait pas besoin pour
** wolf, mais elle ressemblera à ça dans le doom je pense
*/

t_img					*init_image(void *mlx_ptr, int w, int h);
t_texture				*init_tx(char *path, t_vec2 size,
		int nframe);
t_sprite				*init_sprite(t_texture *tx, t_u32 mod, int cd,
		t_vec2 pos);
int						apply_tx(t_texture txt, t_img *img, t_vec2 pos,
		int frame);
int						apply_sprite(t_sprite *spr, t_img *img);
t_texture				*tx_scaleto(t_texture *src, int x, int y);
t_texture				*tx_scaleby(t_texture *src, float scale);
void					clean_image(t_img *img, int width, int height);
void					close_image(t_img *img, void *mlx_ptr, int width,
		int height);
void					close_tx(t_texture **p);
void					close_sprite(t_sprite **sprite);
int						trigger_sprite(t_sprite *sprite);
int						apply_tx_scaled(t_texture txt, t_img *img, t_vec2 pos,
	float scale);

/*
** trace :
*/

void					init_anim_color(t_bresenham *b, int cwh[4],
	float scl_bert[2], t_vecf2 tr);
t_bresenham				init_trace(t_point p[2], t_vecf3 z);
void					need_px(t_bresenham *b, t_img *img);
void					line(t_bresenham b, t_img *img);
#endif
