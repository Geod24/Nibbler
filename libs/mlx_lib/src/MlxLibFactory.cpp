#include	"NibblerMlx.hh"

IGraphicLib	*getLib(unsigned int SquareSize, EventReceiver ptr,
			unsigned int WinHeight, unsigned int WinWidth,
			const std::string& WinName, int BGColor)
{
  return (new MlxLib(SquareSize, ptr, WinHeight, WinWidth,
		     WinName, BGColor));
}
