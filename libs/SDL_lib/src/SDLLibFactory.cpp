//
// SDLLibFactory.cpp for nibbler in /home/robein_a//Prog/C++/Nibbler/nibbler-2015-lang_m/libs/SDL_lib/src
//
// Made by arthur robein
// Login   <robein_a@epitech.net>
//
// Started on  Sun Mar 18 02:28:56 2012 arthur robein
// Last update Sun Mar 18 03:31:19 2012 arthur robein
//

#include        <SDL/SDL.h>
#include        "NibblerSDL.hh"

IGraphicLib     *getLib(unsigned int SquareSize, EventReceiver ptr,
                        unsigned int WinHeight, unsigned int WinWidth,
                        const std::string& WinName, int BGColor)
{
  return (new SDLLib(SquareSize, ptr, WinHeight, WinWidth,
                        WinName, BGColor));
}
