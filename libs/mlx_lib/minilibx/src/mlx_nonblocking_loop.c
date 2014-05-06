/*
** mlx_loop.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Wed Aug  2 18:58:11 2000 Charlie Root
** Last update Sun Mar 18 22:18:04 2012 mathias lang
*/
#include	<time.h>
#include	"mlx_events.h"
#include	"mlx_int.h"

extern int	(*(mlx_int_param_event[]))();

/*
 * Changed from int to void (Then you can thread it =D )
 */

#define MLXKEY_UP	111
#define MLXKEY_DOWN	116
#define MLXKEY_RIGHT	114
#define MLXKEY_LEFT	113
#define MLXKEY_ESCAPE	9

void		*mlx_nonblocking_loop(t_xvar *xvar, int timeout)
{
  static int		ent = 0;
  XEvent		ev;

  (void)timeout;
  if (!ent) {
    XSelectInput(xvar->display, xvar->win_list->window, KeyPressMask);
    ++ent;
  }
  while (XPending(xvar->display))
    {
      XNextEvent(xvar->display, &ev);
      if (ev.type != KeyPress)
	continue;
      switch (ev.xkey.keycode) {
      case MLXKEY_UP:
	return (MLXEV_KEY_UP);
      case MLXKEY_DOWN:
	return (MLXEV_KEY_DOWN);
      case MLXKEY_RIGHT:
	return (MLXEV_KEY_RIGHT);
      case MLXKEY_LEFT:
	return (MLXEV_KEY_LEFT);
      default:
	return (MLXEV_NOTHING);
      }
    }
  return (MLXEV_NOTHING);
}
