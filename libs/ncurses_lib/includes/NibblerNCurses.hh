//
// NibblerNCurses.hh for nibbler in /data/code/C++/nibbler-2015-lang_m/libs/testLib
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Wed Mar 14 17:27:29 2012 mathias lang
// Last update Sun Mar 18 14:17:57 2012 mathias lang
//
#pragma once

#include		<curses.h>
#include		"libABI.hh"

#define FOOD_CHAR	'x'
#define HEAD_CHAR	'o'
#define BODY_CHAR	'#'
#define TAIL_CHAR	';'

class NCurseLib : public IGraphicLib {
public:
  NCurseLib(unsigned int SquareSize, EventReceiver ptr,
	    unsigned int WinHeight, unsigned int WinWidth,
	    const std::string& WinName, int BGColor);
  virtual int	init(void);
  virtual Event	event(void);
  virtual int	redraw(const std::list<Position>&, const Position&);
  virtual	~NCurseLib(void);

  virtual const std::string&	lastError(void) const
  { return _lerr; }
  virtual void			cleanError(void)
  { _lerr = "Success"; }

private:
  void		st_draw_snake(const Position& v);
  int		draw_snake(const std::list<Position>& pos);
  int		draw_food(const Position& pos);

  unsigned int	_sqsize;	// This is ignored
  EventReceiver	_fptr;		// Unused
  unsigned int	_h;
  unsigned int	_w;
  std::string	_wname;		// Unused
  int		_bgcol;		// Unused
  WINDOW*	_win;
  std::string	_lerr;
};
