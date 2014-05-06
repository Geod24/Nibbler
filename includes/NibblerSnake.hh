#pragma once

#include	"NibblerTypes.hh"

class Snake : public IPlayer {
public:
  Snake(int h, int w);
  virtual int			move(Event e);
  int				noEvent(void);
  int				moveRight(void);
  int				moveLeft(void);
  int				moveUp(void);
  int				moveDown(void);
 
  virtual const Position&	getHeadPosition(void) const;
  virtual const Position&	getTailPosition(void) const;
  virtual const std::list<Position>&	getPositions(void) const;
  virtual bool			isOnPosition(const Position& coords) const;
  virtual int			getSize(void) const;
  virtual bool			collision(int height, int width) const;
  virtual bool			check_food(const Position& food);

private:
  std::list<Position>		_pos;
  int (Snake::*const fptrTab[5])(void);
  MovementType			_last;

  bool				if_eat_that(const Position& o) const;
};
