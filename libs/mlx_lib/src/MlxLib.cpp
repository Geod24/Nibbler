//
// MlxLib.cpp for Nibbler in /data/code/C++/nibbler-2015-lang_m/libs/mlx_lib
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Sun Mar 18 01:08:36 2012 mathias lang
// Last update Sun Mar 18 22:14:19 2012 mathias lang
//
#include        <unistd.h>
#include	<functional>
#include	<algorithm>
#include	<sstream>
#include	"NibblerMlx.hh"

static void	my_bzero(char *p, size_t n)
{
  for (size_t i = 0; i < n; ++i) {
    p[i] = 0;
  }
}

MlxLib::MlxLib(unsigned int SquareSize, EventReceiver ptr,
		     unsigned int WinHeight, unsigned int WinWidth,
		     const std::string& WinName, int BGColor)
  : _sqsize(SquareSize), _fptr(ptr), _h(WinHeight), _w(WinWidth),
    _wname(WinName), _bgcol(BGColor), _lerr("Success"),
    _mlx(0), _win(0), _img(0)
{}

int	MlxLib::init(void)
{
  std::stringstream	_val;

  /* ************** Check height and width max values ************** */
  if ((_h * _sqsize) > HEIGHT_MAX) {
    _val << "height must be < " << (HEIGHT_MAX / _sqsize);
    _lerr = _val.str();
    return (LIB_FAILURE);
  }
  if ((_w * _sqsize) > WIDTH_MAX) {
    _val << "width must be < " << (WIDTH_MAX / _sqsize);
    _lerr = _val.str();
    return (LIB_FAILURE);
  }
  /* **************************************************************** */

  if (0 == (_mlx = mlx_init())) {
    _lerr = "mlx_init() failed!";
    return (LIB_FAILURE);
  }

  if (0 == (_win = mlx_new_window(_mlx, (_w * _sqsize), (_h * _sqsize),
  				  _wname.c_str()))) {
    _lerr = "window creation failed!";
    return (LIB_FAILURE);
  }

  if (0 == (_img = mlx_new_image(_mlx, (_w * _sqsize), (_h * _sqsize)))) {
    _lerr = "image creation failed!";
    return (LIB_FAILURE);
  }

  if (0 == (_data = mlx_get_data_addr(_img, &_bpp, &_szline, &_endian))) {
    _lerr = "unable to fetch basic data (mlx_get_data_addr() returned 0)";
    return (LIB_FAILURE);
  }

  draw_walls();
  mlx_do_key_autorepeaton(_mlx);
  return (LIB_SUCCESS);
}

extern int _mlx_loop;

MlxLib::~MlxLib(void)
{
  if (_mlx && _win)
    mlx_destroy_window(_mlx, _win);
  if (_img)
    free(_img); // No damn mlx_destroy_image
  free(_mlx);
}

/* **************************** GRAPHIC *************************** */

# define IMG_POS	((y * _szline) + (x * (_bpp / 8)))

void	MlxLib::pixel_to_image(int x, int y, int color)
{
  int	r = (_endian != 1) ? (color % 0x100) : ((color >> 16) % 0x100);
  int	g = (color >> 8) % 0x100;
  int	b = (_endian != 1) ? ((color >> 16) % 0x100) : (color % 0x100);
  int	decal = (_endian != 1) ? (0) : (1);

  _data[IMG_POS + decal] = r;
  _data[IMG_POS + decal + 1] = g;
  _data[IMG_POS + decal + 2] = b;
}

void	MlxLib::draw_square(const Position& p, int color)
{
  draw_square(p.x, p.y, color);
}

void	MlxLib::draw_square(int x_origine, int y_origine, int color)
{
  x_origine *= _sqsize;
  y_origine *= _sqsize;
  for (int y = y_origine; y < (y_origine + _sqsize); y++) {
    for (int x = x_origine; x < (x_origine + _sqsize); x++) {
      pixel_to_image(x, y, TCOLOR(color));
    }
  }
}

/*
 * \o\ /o/
 *  |   |
 * />\ /!\
 *---------
 */

int	MlxLib::draw_snake(const std::list<Position>& pos)
{
  std::list<Position>::const_iterator	b = pos.begin();
  std::list<Position>::const_iterator	end = pos.end();

  draw_square((*b).x, (*b).y, HEAD_COLOR);
  b++;
  end--;
  draw_square((*end).x, (*end).y, TAIL_COLOR);
  for_each(b, end, std::bind(static_cast<void (MlxLib::*)(const Position&, int)>(&MlxLib::draw_square), this, std::placeholders::_1, BODY_COLOR));
  return (LIB_SUCCESS);
}

int	MlxLib::draw_food(const Position& pos)
{
  draw_square(pos.x, pos.y, APPLE_COLOR);
  return (LIB_SUCCESS);
}

void	MlxLib::draw_walls(void)
{
  for (unsigned int w_x = 0; w_x < _w; w_x++)
    draw_square(w_x, 0, WALL_COLOR);
  for (unsigned int w_x = 0; w_x < _w; w_x++)
    draw_square(w_x, (_h - 1), WALL_COLOR);
  for (int w_y = 1; w_y < (_h - 1); w_y++) {
    draw_square(0, w_y, WALL_COLOR);
    draw_square((_w - 1), w_y, WALL_COLOR);
  }
}

void		MlxLib::clear_game(void)
{
  int		y = _sqsize * _szline;

  while ((y / (_sqsize * _szline)) < (_h - 1)) {
    my_bzero(_data + y + (_sqsize * _bpp / 8),
	     _szline - (2 * _sqsize * (_bpp / 8)));
    y += _szline;
  }
}

int		MlxLib::redraw(const std::list<Position>& pos,
			       const Position& food)
{
  clear_game();
  draw_snake(pos);
  draw_food(food);
  repaint();
  return (LIB_SUCCESS);
}

int		MlxLib::repaint(void)
{
  mlx_put_image_to_window(_mlx, _win, _img, 0, 0);
  return (LIB_SUCCESS);
}

/* ************************* EVENT HANDLING ************************ */

Event		MlxLib::event(void)
{
  int		ev;

  usleep(50000);
  if ((ev = mlx_nonblocking_loop(_mlx, 10000))) {
    switch (ev) {
    case MLXEV_KEY_UP:
      return (KeyUp);
    case MLXEV_KEY_DOWN:
      return (KeyDown);
    case MLXEV_KEY_RIGHT:
      return (KeyRight);
    case MLXEV_KEY_LEFT:
      return (KeyLeft);
    case MLXEV_KEY_ESCAPE:
      return (KeyEscape);
    default:
      return (NoEvent);
    }
  }
  usleep(50000);
  return (NoEvent);
}
