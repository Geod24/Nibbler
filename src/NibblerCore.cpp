#include	<dlfcn.h>
#include	<iostream>
#include	"libABI.hh"
#include	"NibblerCore.hh"

#define	INITIAL_SIZE	4

typedef IGraphicLib*	(*factPtr)(unsigned int, EventReceiver,
				   unsigned int, unsigned int,
				   const std::string&, int);

NibblerCore::NibblerCore(int height, int width, IPlayer *sn)
  : _h(height), _w(width), _sohandler(0), lib(0), snake(sn), timer(100000)
{}

NibblerCore::~NibblerCore()
{
  delete lib;
  /*
   * dlclose doesn't check if void* == NULL...
   */
  if (this->_sohandler != 0) {
    if (0 != dlclose(this->_sohandler))
      std::cerr << dlerror() << std::endl;
  }
  delete snake;
}

int	NibblerCore::getGraphicLib(char *path)
{
  factPtr	fact;

  /*
   * Initialization
   */
  if (0 == (this->_sohandler = dlopen(path, RTLD_NOW)))
    throw new LibError(dlerror());
  /*
   * Cleaning old value of dlerror.
   * This allow us to check if a NULL return is an error or not.
   */
  (void)dlerror();
  /*
   * NB: This is _NOT_ ISO compliant
   * (but it must have been discarded from ISO since real mode isn't used...).
   */
  if (0 == (fact = reinterpret_cast<factPtr>(dlsym(this->_sohandler, FACTORYSYM))))
    throw new LibError(dlerror());
  if (0 == (lib = fact(SQUARE_SIZE, 0, _h, _w, WIN_NAME, FONT_COLOR)))
    throw new LibError("Factory returned no object!");
  if (LIB_FAILURE == lib->init())
    throw new LibError("Lib initialization failed: " + lib->lastError());
  return (0);
}

static void	createNewFood(Position* food, int h, int w)
{
  /*
   * Must be < (h||w) -1 && > 0 (Borders)
   */
  food->x = (rand() % (w - 2)) + 1;
  food->y = (rand() % (h - 2)) + 1;
}

int	NibblerCore::run(void)
{
  Position	food;
  Event		e;

  do {
    createNewFood(&food, _h, _w);
  } while (snake->isOnPosition(food));
  if (LIB_FAILURE == lib->redraw(snake->getPositions(), food))
    throw new LibError("Initial draw failed: " + lib->lastError());
  while (42) {
    e = lib->event();
    switch (e) {
    case KeyEscape:
      return (snake->getSize() - INITIAL_SIZE);
    default:
      (void)snake->move(e);
      if (LIB_FAILURE == lib->redraw(snake->getPositions(), food))
	throw new LibError("redraw (movement) failed: " + lib->lastError());
    }
    if (snake->collision(_h, _w))
      return (-1 * (snake->getSize() - INITIAL_SIZE));
    if (snake->check_food(food)) {
      do {
	createNewFood(&food, _h, _w);
      } while (snake->isOnPosition(food));
      if (LIB_FAILURE == lib->redraw(snake->getPositions(), food))
      	throw new LibError("Redraw (eat food) failed");
    }
  }
}
