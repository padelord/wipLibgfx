#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <SDL2/SDL.h>
#include "libft.h"

typedef unsigned int t_u32;

t_u32	ft_abs(int n)
{
	return (n < 0 ? (t_u32)(-n) : (t_u32)n);
}

void	ft_fill(SDL_Surface *img, t_u32 color)
{
	int	i;
	int	j;
	int hx;
	int hy;
	int	dx;
	int	dy;

	hx = img->w / 2;
	hy = img->h / 2;
	i = -1;
	while (++i < img->h)
	{
		j = -1;
		while (++j < img->w)
		{
			dx = ft_abs(i - hx);
			dy = ft_abs(j - hy);
			color = dx * dx + dy * dy;
			((t_u32*)img->pixels)[i * img->w + j] = color;
		}
	}
}

void	ft_bat()
{
	int secs, pct;

	if (SDL_GetPowerInfo(&secs, &pct) == SDL_POWERSTATE_ON_BATTERY)
	{
		printf("La batterie prend cher: ");
		if (secs == -1)
			printf("(unknown time left)\n");
		else
			printf("(il reste %d minutes and %d secondes)\n", secs / 60, secs % 60);
		if (pct == -1)
			printf("(unknown percentage left)\n");
		else
			printf("(%d percent left)\n", pct);
	}
}

void	printwindowevent(SDL_Event *event)
{
	switch (event->window.event)
	{
		case SDL_WINDOWEVENT_SHOWN:
			printf("Window %d shown\n", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
		printf("Window %d hidden\n", event->window.windowID);
		break;
		case SDL_WINDOWEVENT_EXPOSED:
		printf("Window %d exposed\n", event->window.windowID);
		break;
		case SDL_WINDOWEVENT_MOVED:
		printf("Window %d moved to %d,%d\n",
				event->window.windowID, event->window.data1,
				event->window.data2);
		break;
		case SDL_WINDOWEVENT_RESIZED:
		printf("Window %d resized to %dx%d\n",
				event->window.windowID, event->window.data1,
				event->window.data2);
		break;
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		printf("Window %d size changed to %dx%d\n",
				event->window.windowID, event->window.data1,
				event->window.data2);
		break;
	case SDL_WINDOWEVENT_MINIMIZED:
		printf("Window %d minimized\n", event->window.windowID);
		break;
	case SDL_WINDOWEVENT_MAXIMIZED:
		printf("Window %d maximized\n", event->window.windowID);
		break;
	case SDL_WINDOWEVENT_RESTORED:
		printf("Window %d restored\n", event->window.windowID);
		break;
	case SDL_WINDOWEVENT_ENTER:
		printf("Mouse entered window %d\n",
				event->window.windowID);
		break;
	case SDL_WINDOWEVENT_LEAVE:
		printf("Mouse left window %d\n", event->window.windowID);
		break;
	case SDL_WINDOWEVENT_FOCUS_GAINED:
		printf("Window %d gained keyboard focus\n",
				event->window.windowID);
		break;
	case SDL_WINDOWEVENT_FOCUS_LOST:
		printf("Window %d lost keyboard focus\n",
				event->window.windowID);
		break;
	case SDL_WINDOWEVENT_CLOSE:
		printf("Window %d closed\n", event->window.windowID);
		break;
	case SDL_WINDOWEVENT_TAKE_FOCUS:
		printf("Window %d is offered a focus\n", event->window.windowID);
		break;
	case SDL_WINDOWEVENT_HIT_TEST:
		printf("Window %d has a special hit test\n", event->window.windowID);
		break;
	default:
		printf("Window %d got unknown event %d\n",
				event->window.windowID, event->window.event);
		break;
	}
}

int		main(int ac, char **av)
{
	SDL_Window		*win;
	SDL_Surface		*img;
	SDL_Surface		*wini;
	SDL_Event		event;

	(void)av;
	(void)ac;
	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)))
	{
		printf("error while Init\n");
		return (0);
	}
	if (!(win = SDL_CreateWindow("Bob Rasowsky!!!", 0, 0, 1080, 720, 0)))
	{
		printf("error with window\n");
		return (0);
	}
	SDL_Delay(200);
	SDL_DestroyWindow(win);
	if (!(img = SDL_LoadBMP("test/bob.bmp")))
		printf("Problem getting bob.bmp");
	else
	{
		//printf("img size %dx%d\n", img->w, img->h);
		if ((win = SDL_CreateWindow("my Window", 0, 0, img->w, img->h, 0)))
		{
			wini = SDL_GetWindowSurface(win);
		//	SDL_PollEvent(&event);
			if (event.type == SDL_FIRSTEVENT)
				printf("firstevent\n");
			ft_fill(wini, 0x440000);
			SDL_UpdateWindowSurface(win);
			SDL_BlitSurface(img, 0, wini, 0);
			SDL_UpdateWindowSurface(win);
			SDL_Delay(1000);
			SDL_DestroyWindow(win);
		}
		else
			printf("error with window\n");
		//SDL_FreeSurface(img);
	}
	if (!(win = SDL_CreateWindow("my window", 0, 0, 1080, 720, 0)))
	{
		printf("error creating last window\n");
		return (1);
	}
	SDL_KeyboardEvent *kb;
	SDL_MouseMotionEvent *mouse;
	int	run = 1;
	wini = SDL_GetWindowSurface(win);
//	SDL_ShowCursor(SDL_DISABLE);
	int	lockm = 0;
	printf(" Scancode |  keysym  |   names  \n");
	while (run)
	{
		ft_fill(wini, 0x440000);
		SDL_BlitSurface(img, 0, wini, 0);
		SDL_UpdateWindowSurface(win);
		if (lockm)
			SDL_WarpMouseInWindow(win, 540, 360);
		while (SDL_PollEvent(&event))
		{
			if (lockm && event.type == SDL_MOUSEMOTION)
			{
//				printf("%dx%d\n", event.motion.x, event.motion.y);
				mouse = (SDL_MouseMotionEvent*)&event;
//				if (mouse->x != 540 && mouse->y != 360)
//					printf("mouse moved in %dx%d\n", mouse->x - 540, mouse->y - 360);
			}
			if (event.type == SDL_KEYDOWN)
			{
				printf("%10d|%10d|\"%s\"/\"%s\"\n", event.key.keysym.scancode, event.key.keysym.sym, SDL_GetScancodeName(event.key.keysym.scancode), SDL_GetKeyName(event.key.keysym.sym));
				//printf("scancode : %10d : %s\nkeysym   : %10d : %s\n", event.key.keysym.scancode, SDL_GetScancodeName(event.key.keysym.scancode), event.key.keysym.sym, SDL_GetKeyName(event.key.keysym.sym));
				kb = (SDL_KeyboardEvent*)&event;
//				if ((int)(kb->keysym.scancode) == 44)
//					lockm = (lockm == 1 ? 0 : 1);
				if ((int)(kb->keysym.scancode) == 41)
				{
//					SDL_ShowCursor(SDL_ENABLE);
					SDL_FreeSurface(img);
					SDL_DestroyWindow(win);
					SDL_Quit();
					run = 0;
				}
				//printf("scancode: %d\nkeysym: %d\nmod: %hu\n", kb->keysym.scancode, kb->keysym.sym, kb->keysym.mod);
				//printf("key down\n");
			}
//			if (event.type == SDL_KEYUP)
//				printf("key up\n");
			if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					SDL_DestroyWindow(win);
					SDL_Quit();
					run = 0;
				}
				//printwindowevent(&event);
			}
		}
		SDL_Delay(100);
	}
}
