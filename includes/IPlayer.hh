//
// IPlayer.hh for Nibbler in /data/code/C++/nibbler-2015-lang_m
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Sun Mar 18 01:39:53 2012 mathias lang
// Last update Sun Mar 18 14:12:17 2012 mathias lang
//
#pragma once

#include	<list>

/*
 * Hold Snake's and food's position
 * Contained in a list for snake.
 * Members are public because it makes no sense to make getter/setters...
 * It was originaly a struct, turned into a class for algorithms
 */
class Position {
public:
  int	x;
  int	y;
  bool	operator==(const Position& other) const
  { return (other.x == x && other.y == y); }
};

/* ***************** Lib Communication ********************* */
typedef enum {
  NoEvent = 0,
  KeyRight = 1,
  KeyLeft = 2,
  KeyUp = 3,
  KeyDown = 4,
  KeyEscape = 5
}	Event;

/* ********************* IPlayer *************************** */
class IPlayer {
public:
  virtual ~IPlayer() {}
  virtual int			move(Event e = NoEvent) = 0;

  /*
   * Getters
   */
  virtual const Position&	getHeadPosition(void) const = 0;
  virtual const Position&	getTailPosition(void) const = 0;
  virtual bool			isOnPosition(const Position&) const = 0;
  virtual int			getSize(void) const = 0;
  virtual const std::list<Position>&	getPositions(void) const = 0;
  virtual bool			collision(int, int) const = 0;
  virtual bool			check_food(const Position&) = 0;
};
