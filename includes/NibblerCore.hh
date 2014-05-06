//
// NibblerCore.hh for Nibbler in /data/code/C++/nibbler-2015-lang_m
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Sun Mar 11 05:15:17 2012 mathias lang
// Last update Sun Mar 18 17:28:05 2012 mathias lang
//
#pragma once

#include			<vector>
#include			"NibblerTypes.hh"
#define WIDTH_MIN		10
#define HEIGHT_MIN		10
#define SQUARE_SIZE		20
#define WIN_NAME		"Nibbler: We love sssssnakessssss!"

#define BLACK			0x00
#define FONT_COLOR		BLACK

class NibblerCore {
public:
  NibblerCore(int height, int width, IPlayer *sn);
  ~NibblerCore();
  int		getGraphicLib(char *path);
  int		run(void);

private:
  void		initSnake(void);

  int		_h;
  int		_w;
  void*		_sohandler;
  IGraphicLib*	lib;
  IPlayer*	snake;
  int		timer;

 // Not implemented
  NibblerCore&	operator=(const NibblerCore& other);
  NibblerCore(const NibblerCore& other);
};
