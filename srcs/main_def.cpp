/*
** main_def.cpp for cpp_arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Tue Mar 14 16:23:58 2017 Vincent Pain
** Last update	Tue Mar 28 21:20:10 2017 Vincent Pain
*/

#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <string>
#include "Core.hpp"

void	help()
{
  std::cout << "Usage: ./arcade [LIB]" << std::endl << std::endl << "List of libraries:" << std::endl;
  std::cout << std::endl << "\t-ncurses\t->\t./lib/lib_arcade_ncurses.so" << std::endl;
  std::cout << "\t-SDL\t\t->\t./lib/lib_arcade_SDL.so" << std::endl;
  std::cout << "\t-openGL\t\t->\t./lib/lib_arcade_openGL.so" << std::endl;
  std::cout << "\t-snake\t\t->\t./lib/lib_arcade_snake.so" << std::endl;
  std::cout << "\t-pacman\t\t->\t./lib/lib_arcade_pacman.so" << std::endl;
}


void		intro()
{
  std::string	name;
  std::cout << "List of available libraries:" << std::endl;
  std::cout << "\t-ncurses" << std::endl;
  std::cout << "\t-SDL" << std::endl;
  std::cout << "\t-openGL" << std::endl << std::endl;
  std::cout << "List of available games:" << std::endl;
  std::cout << "\t-snake" << std::endl << "\t-pacman" << std::endl << std::endl;
  std::cout << "What's your name ?" << std::endl;
  std::cin >> name;
  std::cout << "OK, your name is " << name << " !" << std::endl;
}
void		check_lib(std::string libused, int &nb, int &game)
{
  if (libused == "./lib/lib_arcade_ncurses.so"
      || libused == "lib/lib_arcade_ncurses.so")
    nb = 2;
  else if (libused == "./lib/lib_arcade_SDL.so"
	   || libused == "lib/lib_arcade_SDL.so")
    nb = 0;
  else if (libused == "./lib/lib_arcade_openGL.so"
	   || libused == "lib/lib_arcade_openGL.so")
    nb = 1;
  else if (libused == "./games/lib_arcade_snake.so"
	   || libused == "games/lib_arcade_snake.so")
    game = 0;
  else if (libused == "./games/lib_arcade_pacman.so"
	   || libused == "games/lib_arcade_pacman.so")
    game = 1;
}

int		main(int ac, char **av)
{
  void		*dir;
  char		*str;
  int		nb = -1, game = -1;
  Core		core;
  
  if (ac != 2)
    {
      help();
      return (0);
    }
  if ((dir = dlopen(av[1], RTLD_LAZY)) != NULL)
    check_lib(av[1], nb, game);
  str = dlerror();
  if (str != NULL)
    {
      std::cout << str << std::endl;
      help();
      return (0);
    }
  intro();
  if (game == -1)
    game = core.play_menu(1);
  if (game == 1)
    {
      if (nb == -1)
        nb = core.play_menu(2);
      core.choice_libg(nb, dir);
      core.play_game2(dir, nb);
    }
  else if (game == 0)
    {
      if (nb == -1)
        nb = core.play_menu(2);      
      core.choice_libg(nb, dir);
      core.play_game(dir, nb);
    }
}
