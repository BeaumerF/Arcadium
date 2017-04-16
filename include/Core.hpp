//
// core.hpp for  in /home/francois.beaumer/cpp_arcade/include
// 
// Made by François Beaumer
// Login   <francois.beaumer@epitech.net>
// 
// Started on  Thu Apr  6 17:25:30 2017 François Beaumer
// Last update Sun Apr 16 16:09:23 2017 François Beaumer
//

#include "snake.hpp"
#include "pacman.hpp"

#pragma once

class Core
{
public:
  Core() { };
  virtual	~Core() { };
  virtual void	play_game(void *dir_graph, int nb);
  virtual void	play_game2(void *dir_graph, int nb);
  virtual int   play_menu(int choice);
  virtual void  lib_up(int &nb, void *&dir_graph);
  virtual void  lib_down(int &nb, void *&dir_graph);
  virtual void	init_map(char tab[LENGHT][WIDTH], int const map);
  virtual void  struct_init(t_phantom &a, t_phantom &b,
			    t_phantom &c, t_phantom &d);
  virtual void	choice_libg(int const nb, void *&dir) const;
  virtual int	pac_check_move(int const key, char tab[LENGHT][WIDTH], void *dir_game) const;
  virtual int	snake_check_move(int const key, int &tail, char tab[LENGHT][WIDTH], void *dir_game, int &count) const;
};
