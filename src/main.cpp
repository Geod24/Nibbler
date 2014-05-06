#include	<sstream>
#include	<cstdlib>
#include	<iostream>
#include	"libABI.hh"
#include	"NibblerCore.hh"
#include	"NibblerSnake.hh"

static void	print_score_message(int score)
{
  if (score == 0)
    std::cout << "You are really, really bad..." << std::endl;
  if (score > 0)
    std::cout << "Ragequit ? Anyway, your score is " << score << std::endl;
  if (score < 0)
    std::cout << "Hit that noob !! You only got " << -1 * score << std::endl;
}

static int	check_args(int ac, char **av, int *h, int *w)
{
  std::stringstream	streamh;
  std::stringstream	streamw;

  if (ac != 4) {
    std::cerr << "Usage: " << av[0] << " largeur hauteur lib_path"
	      << std::endl;
    return (-42);
  }
  streamw << av[1];
  streamh << av[2];
  streamw >> *w;
  streamh >> *h;
  if (*w < WIDTH_MIN || *w > WIDTH_MAX) {
    std::cerr << "Error: width must be " << WIDTH_MIN << " < width < "
	      << WIDTH_MAX << std::endl;
    return (-42);
  }
  if (*h < HEIGHT_MIN || *h > HEIGHT_MAX) {
    std::cerr << "Error: height must be " << HEIGHT_MIN << " < height < "
	      << HEIGHT_MAX << std::endl;
    return (-42);
  }
  return (0);
}

int		main(int ac, char **av)
{
  NibblerCore	*core;
  IPlayer	*snake;
  int		height;
  int		width;
  int		score = 0;
  
  if (check_args(ac, av, &height, &width))
    return (EXIT_FAILURE);
  snake = new Snake(height, width);
  core = new NibblerCore(height, width, snake);
  srand(time(0));
  try {
    if (-1 == core->getGraphicLib(av[3])) {
      delete core;
      return (EXIT_FAILURE);
    }
    score = core->run();
  }
  catch (myException* excp) {
    /*
     * Some lib (ncurses ie) may avoid printing on cerr.
     */
    delete core;
    std::cerr << excp->what() << std::endl;
    delete excp;
    return (EXIT_FAILURE);
  }
  /* Cleanup */
  delete core;
  print_score_message(score);
  return (EXIT_SUCCESS);
}
