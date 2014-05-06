//
// NibblerTypes.hh for Nibbler in /data/code/C++/nibbler-2015-lang_m
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Sun Mar 11 05:06:53 2012 mathias lang
// Last update Sun Mar 18 01:43:09 2012 mathias lang
//
#pragma once

#include	<stdexcept>
#include	<string>
#include	"IPlayer.hh"
#include	"predicates.hh"
#include	"myExceptions.hh"

/* ****************** Main program ******************** */

// Snake last movement
typedef enum {
  Right = 1,
  Left = 2,
  Down = 3,
  Up = 4
}	MovementType;

// For library event handling
typedef void	(IPlayer::*EventReceiver)(Event);
