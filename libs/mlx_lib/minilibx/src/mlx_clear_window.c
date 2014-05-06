/*
** mlx_clear_window.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Thu Sep  7 19:46:15 2000 Charlie Root
** Last update Sun Mar 18 00:57:01 2012 mathias lang
*/
#include	"mlx_int.h"

int		mlx_clear_window(t_xvar *xvar,t_win_list *win)
{
  /*
   * Check it later: No fucking return
   */
  XClearWindow(xvar->display,win->window);
  if (xvar->do_flush)
    XFlush(xvar->display);
  return (42);
}
