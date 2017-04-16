/*
** play_game.cpp for cpp_arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Fri Mar 17 17:22:44 2017 Vincent Pain
** Last update	Sat Mar 18 21:25:07 2017 Vincent Pain
*/

#include <dlfcn.h>
#include <functional>
#include <iostream>
#include "Core.hpp"

void		Core::init_map(char tab[LENGHT][WIDTH], int const map)
{
  int		i = 0;

  if (map == 1)
  {
    std::ifstream file("map/snake", std::ios::in);
    while (i != 21)
    {
      file >> tab[i];
      tab[i][19] = '\0';
      ++i;
      tab[LENGHT/2][WIDTH/2 - 1] = '1';
    }
  }
  else if (map == 2)
  {
    std::ifstream file("map/pac-man", std::ios::in);
    while (i != 21)
    {
      file >> tab[i];
      tab[i][19] = '\0';
      i++;
      tab[LENGHT/2 + 1][WIDTH/2 - 1] = '1';
    }
  }
}

int		Core::snake_check_move(int const key, int &tail, char tab[LENGHT][WIDTH], void *dir_game, int &count) const
{
  int		err = 0;
  int		(*fct)(char[LENGHT][WIDTH],int, int, int*);

  if (key == 0)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int, int *))dlsym(dir_game, "snake_move");
      err = fct(tab, -1, 0, &tail);      
      if (++count < 4)
      {
        fct = (int (*)(char [LENGHT][WIDTH], int, int, int*))dlsym(dir_game, "add_tail");
        fct(tab, -1, 0, &tail);
      }
      return (err);
    }
  else if (key == 2)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int, int*))dlsym(dir_game, "snake_move");
      err = fct(tab, 0, 1, &tail);
      if (++count < 4)
      {
        fct = (int (*)(char [LENGHT][WIDTH], int, int, int*))dlsym(dir_game, "add_tail");
        fct(tab, 0, 1, &tail);
      }
      return (err);
    }
  else if (key == 1)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int, int*))dlsym(dir_game, "snake_move");
      err = fct(tab, 1, 0, &tail);
      if (++count < 4)
      {
        fct = (int (*)(char [LENGHT][WIDTH], int, int, int*))dlsym(dir_game, "add_tail");
        fct(tab, 1, 0, &tail);
      }
      return (err);
    }
  else if (key == 3)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int, int*))dlsym(dir_game, "snake_move");
      err = fct(tab, 0, -1, &tail);
      if (++count < 4)
      {
        fct = (int (*)(char [LENGHT][WIDTH], int, int, int*))dlsym(dir_game, "add_tail");
        fct(tab, 0, -1, &tail);
      }
      return (err);
    }
  return (err);
}

void	Core::lib_up(int &nb, void *&dir_graph)
{
  void	(*fct_void)();
  
  dlclose(dir_graph);
  if (nb == 0)
    {
      ++nb;
      dir_graph = dlopen("./lib/lib_arcade_SDL.so", RTLD_LAZY);
      fct_void = (void (*)())dlsym(dir_graph, "init_window");
      fct_void();
    }
  else if (nb == 2)
    {
      nb = 0;
      dir_graph = dlopen("./lib/lib_arcade_ncurses.so", RTLD_LAZY);
      fct_void = (void (*)())dlsym(dir_graph, "init_window");
      fct_void();
    }
  else if (nb == 1)
    {
      ++nb;
      dir_graph = dlopen("./lib/lib_arcade_openGL.so", RTLD_LAZY);
      fct_void = (void (*)())dlsym(dir_graph, "init_window");
      fct_void();
    }
}

void    Core::lib_down(int &nb, void *&dir_graph)
{
  void	(*fct_void)();

  dlclose(dir_graph);
  if (nb == 2)
    {
      --nb;
      dir_graph = dlopen("./lib/lib_arcade_SDL.so", RTLD_LAZY);
      fct_void = (void (*)())dlsym(dir_graph, "init_window");
      fct_void();
    }
  else if (nb == 1)
    {
      --nb;
      dir_graph = dlopen("./lib/lib_arcade_ncurses.so", RTLD_LAZY);
      fct_void = (void (*)())dlsym(dir_graph, "init_window");
      fct_void();
    }
  else if (nb == 0)
    {
      nb = 2;
      dir_graph = dlopen("./lib/lib_arcade_openGL.so", RTLD_LAZY);
      fct_void = (void (*)())dlsym(dir_graph, "init_window");
      fct_void();
    }
}

void	Core::play_game(void *dir_graph, int nb)
{
  char	tab[LENGHT][WIDTH];
  int	(*fct_tab)(char[LENGHT][WIDTH]);
  void	(*fct_void)();
  int	(*fct)(int, int*);
  void	*dir_game;
  int		ch = 0, ch2 = 0, err = 0, tail = 1, key = 0, count = 0, choice = -1;

  this->init_map(tab, 1);
  
  dir_game = dlopen("./games/lib_arcade_snake.so", RTLD_LAZY);

  fct_void = (void (*)())dlsym(dir_graph, "init_window");
  fct_void();
  
  fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_graph, "display_map");
    fct_tab(tab);
  
  while (err != 42 && ch != 27)
  {
    usleep(250000);
    fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_graph, "get_key");
    ch = fct_tab(tab);
    fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_game, "put_feed");
    fct_tab(tab);
    if (ch == -1)
      ch = ch2;

    fct = (int (*)(int, int *))dlsym(dir_graph, "check_key");
    if ((key = fct(ch, &ch2)) != 42)
    {
      if (key == -21)
        this->lib_up(nb, dir_graph);
      else if (key == 21)
	this->lib_down(nb, dir_graph);
      else if (key == 10)
	{
	  dlclose(dir_game);
	  this->play_game2(dir_graph, nb);
	  return ;
	}
      else if (key == -10)
        {
	  dlclose(dir_game);
	  this->play_game(dir_graph, nb);
	  return ;
	}
      else if (key == 100)
	{
	  dlclose(dir_game);
	  dlclose(dir_graph);
	  choice = this->play_menu(1);
	  if (choice== 1)
	    {
	      nb = this->play_menu(2);
	      this->choice_libg(nb, dir_graph);
	      this->play_game2(dir_graph, nb);
	    }
	  else if (choice == 0)
	    {
	      nb = this->play_menu(2);
	      this->choice_libg(nb, dir_graph);
	      this->play_game(dir_graph, nb);
	    }
	  exit (12);
	}
      err = this->snake_check_move(key, tail, tab, dir_game, count);
    }
    fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_graph, "display_map");
    fct_tab(tab);
  }
    fct_void = (void (*)())dlsym(dir_graph, "close_window");
  fct_void();  

  dlclose(dir_game);
}
