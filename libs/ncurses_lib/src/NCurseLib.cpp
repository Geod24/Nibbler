//
// NCurseLib.cpp for original prankster in /data/code/C++/nibbler-2015-lang_m/libs/testLib
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Wed Mar 14 17:34:43 2012 mathias lang
// Last update Sun Mar 18 05:18:51 2012 mathias lang
//
#include	<sstream>
#include	<algorithm>
#include	<functional>
#include	"NibblerNCurses.hh"

#define	KEY_ESC	27

/*
 * y = hauteur.
 * x = largeur.
 */

/*
 * faire une new win
 * (curs_set(0-1)) => 
 * wborder... => A faire avant chaque refresh
 * WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
 */

NCurseLib::NCurseLib(unsigned int SquareSize, EventReceiver ptr,
		     unsigned int WinHeight, unsigned int WinWidth,
		     const std::string& WinName, int BGColor)
  : _sqsize(SquareSize), _fptr(ptr), _h(WinHeight), _w(WinWidth),
    _wname(WinName), _bgcol(BGColor), _lerr("Success")
{}

int	NCurseLib::init(void)
{
  if (0 == initscr()) {
    _lerr = "initscr() failed";
    return (LIB_FAILURE);
  }
  if (static_cast<unsigned int>(LINES) < _h
      || static_cast<unsigned int>(COLS) < _w) {
    _lerr = "Given size are too big";
    return (LIB_FAILURE);
  }
  if (ERR == curs_set(0)) {
    _lerr = "curse_set() failed";
    return (LIB_FAILURE);
  }
  if (ERR == halfdelay(1)) {
    _lerr = "Setting mode failed";
    return (LIB_FAILURE);
  }
  if (ERR == noecho()) {
    _lerr = "noecho() failed";
    return (LIB_FAILURE);
  }
  if (ERR == keypad(stdscr, TRUE)) {
    _lerr = "keypad() failed";
    return (LIB_FAILURE);
  }
  if (0 == (this->_win = newwin(_h, _w, 0, 0))) {
    _lerr = "Can't allocate new win";
    return (LIB_FAILURE);
  }
  if (ERR == wborder(_win, '|', '|', '-', '-', '+', '+', '+', '+')) {
    _lerr = "Unable to draw borders";
   return (LIB_FAILURE);
  }
  if (ERR == wrefresh(_win)) {
    _lerr = "Refresh failed";
    return (LIB_FAILURE);
  }
  return (LIB_SUCCESS);
}

NCurseLib::~NCurseLib(void)
{
  delwin(_win);
  echo();
  endwin();
}

/* **************************** GRAPHIC *************************** */

void	NCurseLib::st_draw_snake(const Position& v)
{
  if (ERR == mvwaddch(_win, v.y, v.x, BODY_CHAR)) {
    std::stringstream			_merr;
    _merr << "mvwaddch(head) failed at coords " << v.x
	  << " : " << v.y;
    _lerr = _merr.str();
  }
}

int	NCurseLib::draw_snake(const std::list<Position>& pos)
{
  std::list<Position>::const_iterator	b = pos.begin();
  std::list<Position>::const_iterator	end = pos.end();
  std::stringstream			_merr;

  if (ERR == mvwaddch(_win, (*b).y, (*b).x, HEAD_CHAR)) {
    _merr << "mvwaddch(head) failed at coords " << (*b).x
	  << " : " << (*b).y;
    _lerr = _merr.str();
    return (LIB_FAILURE);
  }
  b++;
  end--;
  if (ERR == mvwaddch(_win, (*end).y, (*end).x, TAIL_CHAR)) {
    _merr << "mvwaddch(head) failed at coords " << (*end).x
	  << " : " << (*end).y;
    _lerr = _merr.str();
    return (LIB_FAILURE);
  }
  // Hack
  cleanError();
  /*
   * Wait... What ?
   * La ligne ci-dessous a necessite une heure de debug / google.
   * http://gcc.gnu.org/bugzilla/show_bug.cgi?id=37811
   */
  for_each(b, end, std::bind(&NCurseLib::st_draw_snake, this,
			     std::placeholders::_1));
  // Hack 2nde partie
  if (_lerr != "Success")
    return (LIB_FAILURE);
  return (LIB_SUCCESS);
}

int	NCurseLib::draw_food(const Position& pos)
{
  std::stringstream			_merr;

  if (ERR == mvwaddch(_win, pos.y, pos.x, FOOD_CHAR)) {
    _merr << "mvwaddch(head) failed at coords " << pos.x
	  << " : " << pos.y;
    _lerr = _merr.str();
    return (LIB_FAILURE);
  }
  return (LIB_SUCCESS);
}

/* ************************* EVENT HANDLING ************************ */

Event		NCurseLib::event(void)
{
  int		c;

  /*
   * There may be a bug in halfdelay mode, making screen vanishe on the
   * very first time we get input...
   */
  c = getch();
  switch (c) {
    case KEY_RIGHT:
      return (KeyRight);
    case KEY_LEFT:
      return (KeyLeft);
    case KEY_UP:
      return (KeyUp);
    case KEY_DOWN:
      return (KeyDown);
    case KEY_ESC:
      return (KeyEscape);
    default:
      return (NoEvent);
    }
  timeout(90);
}

int		NCurseLib::redraw(const std::list<Position>& pos, const Position& food)
{
  wclear(_win);
  if (ERR == wborder(_win, '|', '|', '-', '-', '+', '+', '+', '+')) {
    _lerr = "Unable to draw borders";
    return (LIB_FAILURE);
  }
  if (LIB_FAILURE == draw_snake(pos))
    return (LIB_FAILURE);
  if (LIB_FAILURE == draw_food(food))
    return (LIB_FAILURE);
  if (ERR == wrefresh(_win)) {
    _lerr = "Refresh failed";
    return (LIB_FAILURE);
  }
  return (LIB_SUCCESS);
}
