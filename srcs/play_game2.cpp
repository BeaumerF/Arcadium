/*
** play_game2.cpp for arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Tue Apr 04 14:00:41 2017 Vincent Pain
** Last update	Tue Apr 04 15:39:52 2017 Vincent Pain
*/

#include <dlfcn.h>
#include <functional>
#include <iostream>
#include "Core.hpp"

void    Core::choice_libg(int const libg, void *&dir) const
{
  if (libg == 0)
    dir = dlopen("./lib/lib_arcade_SDL.so", RTLD_LAZY);
  else if (libg == 1)
    dir = dlopen("./lib/lib_arcade_openGL.so", RTLD_LAZY);
  else if (libg == 2)
    dir = dlopen("./lib/lib_arcade_ncurses.so", RTLD_LAZY);
}

void		Core::struct_init(t_phantom &a, t_phantom &b,
				  t_phantom &c, t_phantom &d)
{
  a.c = 'a';
  b.c = 'b';
  c.c = 'c';
  d.c = 'd';
  a.last = '0';
  b.last = '0';
  c.last = '0';
  d.last = '0';
  a.last_dir = -1;
  b.last_dir = -1;
  c.last_dir = -1;
  d.last_dir = -1;
}

int	Core::pac_check_move(int const key, char tab[LENGHT][WIDTH], void *dir_game) const
{
  int	err = 0;
  int	(*fct)(char[LENGHT][WIDTH],int, int);

  if (key == 0)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int))dlsym(dir_game, "pac_move");
      err = fct(tab, -1, 0);
      return (err);
    }
  else if (key == 2)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int))dlsym(dir_game, "pac_move");
      err = fct(tab, 0, 1);
      return (err);
    }
  else if (key == 1)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int))dlsym(dir_game, "pac_move");
      err = fct(tab, 1, 0);
      return (err);
    }
  else if (key == 3)
    {
      fct = (int (*)(char [LENGHT][WIDTH], int, int))dlsym(dir_game, "pac_move");
      err = fct(tab, 0, -1);
      return (err);
    }
  return (err);
}


void		Core::play_game2(void *dir_graph, int nb)
{
  int		ch = 0, ch2 = 0, err = 0, key = 0, mod = 0, choice = -1;
  t_phantom     a, b, c, d;
  void		*dir_game;
  char		tab[LENGHT][WIDTH];
  void		(*fct_void)();
  void		(*fct_tabint)(char[LENGHT][WIDTH], int *);
  void		(*fct_phantom)(char[LENGHT][WIDTH], t_phantom *);
  int		(*fct_tab)(char[LENGHT][WIDTH]);
  int		(*fct_tab2)(char[LENGHT][WIDTH]);
  int		(*fct)(int, int *);
  
  this->init_map(tab, 2);
  this->struct_init(a, b, c, d);
  dir_game = dlopen("./games/lib_arcade_pacman.so", RTLD_LAZY);
  fct_void = (void (*)())dlsym(dir_graph, "init_window");
  fct_void();  
  
  fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_graph, "display_map_pac");
  fct_tab(tab);

  while (err != 42 && ch != 27)
    {
      usleep(250000);
      fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_graph, "get_key");
      ch = fct_tab(tab);
      fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_game, "put_feed");
      fct_tab2 = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_game, "game_over");

      if (fct_tab(tab) == 42
	  || fct_tab2(tab) != 42)
	{
	  fct_void = (void (*)())dlsym(dir_graph, "close_window");
	  fct_void();
	  return ;
	}
      
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
	      this->play_game(dir_graph, nb);
	      return ;
	    }
	  else if (key == -10)
	    {
	      dlclose(dir_game);
	      this->play_game2(dir_graph, nb);
	      return ;
	    }
	  else if (key == 100)
	    {
	      dlclose(dir_game);
	      dlclose(dir_graph);
	      choice = this->play_menu(1);
	      if (choice == 1)
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
	  else
	    err = this->pac_check_move(key, tab, dir_game);
	}
      fct_tabint = (void (*)(char [LENGHT][WIDTH], int *))dlsym(dir_game, "init_phantom");
      fct_tabint(tab, &mod);
      fct_phantom = (void (*)(char [LENGHT][WIDTH], t_phantom *))dlsym(dir_game, "move_phantom");
      fct_phantom(tab, &a);
      fct_phantom(tab, &b);
      fct_phantom(tab, &c);
      fct_phantom(tab, &d);
      fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_game, "teleport");
      fct_tab(tab);
      fct_tab = (int (*)(char [LENGHT][WIDTH]))dlsym(dir_graph, "display_map_pac");
      fct_tab(tab);
    }
  fct_void = (void (*)())dlsym(dir_graph, "close_window");
  fct_void();
}
