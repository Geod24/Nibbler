//
// NibblerSDL.hh for nibbler in /home/robein_a//Prog/C++/Nibbler/nibbler-2015-lang_m/libs/SDL_lib/includes
//
// Made by arthur robein
// Login   <robein_a@epitech.net>
//
// Started on  Sun Mar 18 02:19:30 2012 arthur robein
// Last update Sun Mar 18 16:39:20 2012 mathias lang
//

#pragma once

#include	<vector>
#include        <curses.h>
#include        "libABI.hh"

class SDLLib : public IGraphicLib {
public:
  SDLLib(unsigned int SquareSize, EventReceiver ptr,
            unsigned int WinHeight, unsigned int WinWidth,
            const std::string& WinName, int BGColor);
  virtual int   init(void);
  virtual Event	event(void);
  virtual int	redraw(const std::list<Position>&, const Position&);

  virtual const std::string&	lastError(void) const
  { return _lerr; }
  virtual void			cleanError(void)
  { _lerr = "Success"; }

  virtual       ~SDLLib(void);

private:
  void		draw_square(const Position& pos, Uint32 color);
  void		draw_square(unsigned int x, unsigned int y, Uint32 color);
  int		draw_snake(const std::list<Position>& pos);
  int		draw_food(const Position& pos);
  void		clear_screen(void);

  unsigned int  _sqsize;
  EventReceiver _fptr;
  unsigned int  _h;
  unsigned int  _w;
  std::string   _wname;
  int           _bgcol;
  SDL_Surface   *_win;

  std::string	_lerr;
};
