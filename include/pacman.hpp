//
// snake.hpp for  in /home/francois.beaumer/rendu/cpp_arcade
// 
// Made by François Beaumer
// Login   <francois.beaumer@epitech.net>
// 
// Started on  Tue Mar 14 14:15:24 2017 François Beaumer
// Last update Thu Apr  6 18:14:39 2017 François Beaumer
//

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>

#define LENGHT 21
#define WIDTH 20


extern "C"
{
  typedef struct    s_color
  {
    SDL_Surface *mur;
    SDL_Surface *chemin;
    SDL_Surface *pacman;
    SDL_Surface *nouriture;
    SDL_Surface *fantome_rose;
    SDL_Surface *fantome_bleu;
    SDL_Surface *fantome_rouge;
    SDL_Surface *fantome_orange;
  }     t_color;

  typedef struct		s_phantom
  {
    char			c;
    char			last;
    int			last_dir;
  }			t_phantom;


  /*
  ** main.cpp
  */
  int             pac_move(char tab[LENGHT][WIDTH], int x, int y);
  void            init_phantom(char tab[LENGHT][WIDTH], int *x);
  void            move_phantom(char tab[LENGHT][WIDTH], t_phantom *ph);
  int             game_over(char tab[LENGHT][WIDTH]);
  int            teleport(char tab[LENGHT][WIDTH]);

  /*
  ** snake ncurses lib
  */
  void            libuse(char tab[LENGHT][WIDTH]);

  /*
  ** display_ncurse.cpp
  */
  void        display_map_ncurses(char map[LENGHT][WIDTH]);
  int            put_feed(char tab[21][20]);  
  
  /*
  **  init_sdl.cpp
  */

  void	libuse2(char    tab[LENGHT][WIDTH]);
  void		struct_init(t_phantom &a, t_phantom &b,
			    t_phantom &c, t_phantom&d);
}

/*                                                                            
** init_map.cpp                                                               
*/
void            init_map(char tab[LENGHT][WIDTH], int map);
