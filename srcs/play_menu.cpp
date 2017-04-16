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

int     Core::play_menu(int choice)
{
  int		ch = 0, key = 0;
  int   i = 0;
  void *dir_menu;
  int       select = 0;
  int (*fct_get_key)();
  int (*fct_check_key)(int);
  void (*fct_void)();
  void (*fct_display)(int);
  
  if (choice == 1)
  {
    dir_menu = dlopen("./lib/lib_menu_game.so", RTLD_LAZY);
    fct_display = (void (*)(int))dlsym(dir_menu, "display_menu_game");  
  }
  else if (choice == 2)
  {
    dir_menu = dlopen("./lib/lib_menu_graph.so", RTLD_LAZY);
    fct_display = (void (*)(int))dlsym(dir_menu, "display_menu_graph");  
  }
  fct_void = (void (*)())dlsym(dir_menu, "init_window");
  fct_void();
  fct_display(select);
  fct_check_key = (int (*)(int))dlsym(dir_menu, "check_key");
  fct_get_key = (int (*)())dlsym(dir_menu, "get_key");
  fct_get_key();
  while (ch != 27)
    {
      fct_display(select);
      ch = fct_get_key();
      if ((key = fct_check_key(ch)) != 27 && i > 3)
	    {
            if (key != -10)
                select = key;
            if (ch == 13)
                break;
	    }
      else if (ch == 27)
      {
          fct_void = (void (*)())dlsym(dir_menu, "close_window");
          fct_void();
          dlclose(dir_menu);
          exit(0);
      }
      usleep(500000);
      i++;
    }
  fct_void = (void (*)())dlsym(dir_menu, "close_window");
  fct_void();
  dlclose(dir_menu);
  return (select);
}