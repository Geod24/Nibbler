//
// SDLLib.cpp for nibbler in /home/robein_a//Prog/C++/Nibbler/nibbler-2015-lang_m/libs/SDL_lib/src
//
// Made by arthur robein
// Login   <robein_a@epitech.net>
//
// Started on  Sun Mar 18 02:30:21 2012 arthur robein
// Last update Sun Mar 18 16:44:14 2012 mathias lang
//
#include        <SDL/SDL.h>
#include        <unistd.h>
#include        <algorithm>
#include        <functional>
#include	<string>
#include	<sstream>
#include        "NibblerSDL.hh"

SDLLib::SDLLib(unsigned int SquareSize, EventReceiver ptr,
                     unsigned int WinHeight, unsigned int WinWidth,
                     const std::string& WinName, int BGColor)
  : _sqsize(SquareSize), _fptr(ptr), _h(WinHeight), _w(WinWidth),
    _wname(WinName), _bgcol(BGColor), _lerr("Success")
{}

// Upper border

int     SDLLib::init(void)
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

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    _lerr = "SDL_Init The sdl init failed.";
    return (LIB_FAILURE);
  }
  if ((_win = SDL_SetVideoMode(_w * _sqsize, _h * _sqsize,
			       32, SDL_HWSURFACE)) == NULL) {
    _lerr = "SDL_SetVideoMode The sdl set video failed.";
    return (LIB_FAILURE);
  }
  SDL_WM_SetCaption(_wname.c_str(), NULL);
  for (unsigned int w_x = 0; w_x < _w; w_x++)
    draw_square(w_x, 0, WALL_COLOR);
  for (unsigned int w_x = 0; w_x < _w; w_x++)
    draw_square(w_x, (_h - 1), WALL_COLOR);
  for (unsigned int w_y = 1; w_y < (_h - 1); w_y++) {
    draw_square(0, w_y, WALL_COLOR);
    draw_square((_w - 1), w_y, WALL_COLOR);
  }
  return (LIB_SUCCESS);
}

SDLLib::~SDLLib(void)
{
  SDL_Quit();
}

void	SDLLib::draw_square(unsigned int x, unsigned int y, Uint32 color)
{
  SDL_Rect	square;

  square.x = (x * _sqsize);
  square.y = (y * _sqsize);
  square.w = _sqsize;
  square.h = _sqsize;
  SDL_FillRect(_win, &square, color);
}

void	SDLLib::draw_square(const Position& pos, Uint32 color)
{
  draw_square(pos.x, pos.y, color);
}

int     SDLLib::draw_snake(const std::list<Position>& pos)
{
  std::list<Position>::const_iterator b = pos.begin();
  std::list<Position>::const_iterator end = pos.end();

  draw_square((*b).x, (*b).y, HEAD_COLOR);
  b++;
  end--;
  draw_square((*end).x, (*end).y, TAIL_COLOR);
  for_each(b, end, std::bind(static_cast<void (SDLLib::*)(const Position&, Uint32)>(&SDLLib::draw_square), this, std::placeholders::_1, BODY_COLOR));
  return (LIB_SUCCESS);
}

int     SDLLib::draw_food(const Position& pos)
{
  draw_square(pos, SDL_MapRGB(_win->format,
			      (APPLE_COLOR & 0xff0000) >> 16,
			      (APPLE_COLOR & 0xff00) >> 8,
			      APPLE_COLOR & 0xff));
  return (LIB_SUCCESS);
}

void	SDLLib::clear_screen(void)
{
  SDL_Rect	square;

  square.x = _sqsize;
  square.y = _sqsize;
  square.w = (_w - 2) * _sqsize;
  square.h = (_h - 2) * _sqsize;
  SDL_FillRect(_win, &square, _bgcol);
}

int	SDLLib::redraw(const std::list<Position>& sn, const Position& food)
{
  clear_screen();
  draw_snake(sn);
  draw_food(food);
  SDL_Flip(_win);
  return (LIB_SUCCESS);
}

Event	SDLLib::event(void)
{
  SDL_Event	e;
  usleep(100000);
  SDL_PollEvent(&e);
  if (e.type == SDL_QUIT)
    return (KeyEscape);
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      return (KeyUp);
    case SDLK_DOWN:
      return (KeyDown);
    case SDLK_RIGHT:
      return (KeyRight);
    case SDLK_LEFT:
      return (KeyLeft);
    case SDLK_ESCAPE:
      return (KeyEscape);
    default:
      return (NoEvent);
    }
  }
  return (NoEvent);
}
