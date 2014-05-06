#include	<functional>
#include	<algorithm>
#include	"NibblerSnake.hh"

Snake::Snake(int h, int w)
    : fptrTab { &Snake::noEvent, &Snake::moveRight, &Snake::moveLeft,
	&Snake::moveDown, &Snake::moveUp }, _last(Right)
{
  Position	tmp;

  tmp.y = h / 2;
  tmp.x = w / 2 + 1;
  _pos.push_back(tmp);
  tmp.x--;
  _pos.push_back(tmp);
  tmp.x--;
  _pos.push_back(tmp);
  tmp.x--;
  _pos.push_back(tmp);
}

int		Snake::moveUp(void)
{
  Position	npos(_pos.front());

  if (_last == Down)
    return (0);
  ++(npos.y);
  _pos.pop_back();
  _pos.push_front(npos);
  _last = Up;
  return (0);
}

int		Snake::moveDown(void)
{
  Position	npos(_pos.front());

  if (_last == Up)
    return (0);
  --(npos.y);
  _pos.pop_back();
  _pos.push_front(npos);
  _last = Down;
  return (0);
}

int		Snake::moveRight(void)
{
  Position	npos(_pos.front());

  if (_last == Left)
    return (0);
  ++(npos.x);
  _pos.pop_back();
  _pos.push_front(npos);
  _last = Right;
  return (0);
}

int		Snake::moveLeft(void)
{
  Position	npos(_pos.front());

  if (_last == Right)
    return (0);
  --(npos.x);
  _pos.pop_back();
  _pos.push_front(npos);
  _last = Left;
  return (0);
}

int		Snake::noEvent(void)
{
  return (this->*fptrTab[_last])();;
}

int		Snake::move(Event e)
{
  return (this->*fptrTab[e])();
}

const Position&	Snake::getHeadPosition(void) const
{
  return (_pos.front());
}

const Position&	Snake::getTailPosition(void) const
{
  return (_pos.back());
}

bool	Snake::isOnPosition(const Position& coords) const
{
  std::list<Position>::const_iterator	it = _pos.begin();
  std::list<Position>::const_iterator	end = _pos.end();
  std::list<Position>::const_iterator	ret;

  ret = find_if(it, end, std::bind(&equal<Position>,
				   std::placeholders::_1, coords));
  if (ret != end)
    return (true);
  return (false);
}

const std::list<Position>&	Snake::getPositions(void) const
{
  return _pos;
}

int				Snake::getSize(void) const
{
  return _pos.size();
}

bool				Snake::if_eat_that(const Position& o) const
{
  return (o == _pos.front());
}

bool				Snake::collision(int height, int width) const
{
  std::list<Position>::const_iterator	b = _pos.begin();
  std::list<Position>::const_iterator	end = _pos.end();
  std::list<Position>::const_iterator	ret;

  if (_pos.front().x <= 0 || _pos.front().y <= 0)
    return (true);
  if (_pos.front().x >= (width - 1) || _pos.front().y >= (height - 1))
    return (true);
  b++;
  ret = find_if(b, end, std::bind(&Snake::if_eat_that, this,
  				  std::placeholders::_1));
  if (ret != end)
    return (true);
  return (false);
}

bool		Snake::check_food(const Position& food)
{
  if (if_eat_that(food)) {
    _pos.push_back(_pos.back());
    return (true);
  }
  return (false);
}
