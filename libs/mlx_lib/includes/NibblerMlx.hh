//
// NibblerMlx.hh for Nibbler in /data/code/C++/nibbler-2015-lang_m/libs/mlx_lib
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Sun Mar 18 01:06:06 2012 mathias lang
// Last update Sun Mar 18 16:10:32 2012 mathias lang
//
#pragma once

#include			<pthread.h>
#include			"mlx.h"
#include			"libABI.hh"

#define TCOLOR(v)		(mlx_get_color_value(_mlx, v))

#define KEY_ESC			65307
#define KEY_LEFT		65361
#define KEY_UP			65362
#define KEY_RIGHT		65363
#define KEY_DOWN		65364

class MlxLib : public IGraphicLib {
public:
  MlxLib(unsigned int SquareSize, EventReceiver ptr,
	    unsigned int WinHeight, unsigned int WinWidth,
	    const std::string& WinName, int BGColor);
  virtual int	init(void);
  virtual Event	event(void);
  virtual int	redraw(const std::list<Position>&, const Position&);
  virtual	~MlxLib(void);

  virtual const std::string&	lastError(void) const
  { return _lerr; }
  virtual void			cleanError(void)
  { _lerr = "Success"; }

  int		repaint(void);

private:
  void		pixel_to_image(int, int, int);
  void		draw_square(int, int, int);
  void		draw_square(const Position&, int);
  void		clear_game(void);

  int		draw_food(const Position&);
  int		draw_snake(const std::list<Position>&);
  void		draw_walls(void);

  // int		draw_square();

  unsigned int	_sqsize;
  EventReceiver	_fptr;
  unsigned int	_h;
  unsigned int	_w;
  std::string	_wname;
  int		_bgcol;
  std::string	_lerr;

  /*
   * mlx part
   * Revoir ses cours de tek 1, ca n'a pas de prix!
   */
  void		*_mlx;
  void		*_win;
  void		*_img;
  char		*_data;
  int		_bpp;
  int		_szline;
  int		_endian;

  /*
   * Coucou les threads
   */
  pthread_t	eventThread;
};
