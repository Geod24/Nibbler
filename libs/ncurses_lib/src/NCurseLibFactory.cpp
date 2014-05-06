#include	"NibblerNCurses.hh"

IGraphicLib	*getLib(unsigned int SquareSize, EventReceiver ptr,
			unsigned int WinHeight, unsigned int WinWidth,
			const std::string& WinName, int BGColor)
{
  return (new NCurseLib(SquareSize, ptr, WinHeight, WinWidth,
			WinName, BGColor));
}
