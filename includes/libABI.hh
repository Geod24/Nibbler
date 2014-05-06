#pragma once

#include			"NibblerTypes.hh"

/*
 * That's what returned in case of failure.
 */
#define	LIB_SUCCESS		42
#define LIB_FAILURE		-42

/*
 * Screen size
 */
#define HEIGHT_MAX		800
#define WIDTH_MAX		1600

/*
 * http://www.tayloredmktg.com/rgb/
 */
#define BLACK			0x00
#define DARK_ORANGE		0xffa500
#define RED			0xff0000
#define ORANGE			0xff8c00
#define GREEN_YELLOW		0xadff2f
#define FIREBRICK		0xb22222
#define HOT_PINK		0xff69b4

#define APPLE_COLOR		GREEN_YELLOW
#define WALL_COLOR		FIREBRICK
#define HEAD_COLOR		RED
#define TAIL_COLOR		HOT_PINK
#define BODY_COLOR		ORANGE

/*
 * Library interface
 */
class IGraphicLib {
public:
  // Initialization (return value...)
  virtual int	init(void) = 0;
  // Returns event or timeout (NoEvent)
  virtual Event	event(void) = 0;
  // Redraw scene (snake, food)
  virtual int	redraw(const std::list<Position>&, const Position&) = 0;

  // Return a string contraining last error.
  virtual const std::string&	lastError(void) const = 0;
  virtual void			cleanError(void) = 0;

  // Clean the lib...
  virtual	~IGraphicLib(void)		{}

  /*
   * Main graphic stuff
   */
  // const std::string&	getWindowName(void) const = 0;
  // void		setWindowName(const std::string& n);
};

/*
 * Library factory
 * Parameters are constructor's arguments
 */
class GraphicLibFactory {
public:
  static IGraphicLib	*getLib(unsigned int SquareSize,
				EventReceiver ptr,
				unsigned int WinHeight,
				unsigned int WinWidth,
				const std::string& WinName,
				int BGColor);
};

/*
 * Only for dlsym
 */
#define	FACTORYSYM	"_Z6getLibjM7IPlayerFv5EventEjjRKSsi"
