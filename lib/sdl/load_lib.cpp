/*
** load_lib.cpp for cpp_arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Tue Mar 14 16:45:00 2017 Vincent Pain
** Last update	Tue Apr 04 13:55:43 2017 Vincent Pain
*/

#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <iostream>

#include "snake.hpp"

extern "C"

{
  void load_lib() __attribute__ ((constructor));

  void close_lib() __attribute__ ((destructor));

  void load_lib()
  {
    printf("Loading SDL\n");
  }

  void close_lib()
  {
    printf("Unloading SDL\n");
  }

  int        display_map(char tab[LENGHT][WIDTH])
  {
    SDL_Surface *rectangle_b = NULL, *rectangle_r = NULL, *rectangle_v = NULL;
    SDL_Surface *ecran = NULL;
    SDL_Rect pos;

    ecran = SDL_SetVideoMode(665, 735, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Arcade", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    rectangle_b = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    rectangle_r = SDL_CreateRGBSurface(SDL_HWSURFACE, 15, 15, 32, 0, 0, 0, 0);
    rectangle_v = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    SDL_FillRect(rectangle_b, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_FillRect(rectangle_r, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
    SDL_FillRect(rectangle_v, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

    pos.x = 0;
    pos.y = 0;
    SDL_FillRect(ecran, NULL, SDL_MapRGB((ecran)->format, 255, 255, 255));

    for (int y = 0; y < LENGHT; y++)
      {
	for (int x = 0; x < WIDTH; x++)
	  {
	    pos.x = x * 35;
	    pos.y = y * 35;
	    if (tab[y][x] == '*')
	      SDL_BlitSurface(rectangle_b, NULL, ecran, &pos);
	    else if (tab[y][x] == '$')
	      {
		pos.x += 10;
		pos.y += 10;
		SDL_BlitSurface(rectangle_r, NULL, ecran, &pos);
	      }
	    else if (tab[y][x] != '0')
	      {
		SDL_BlitSurface(rectangle_v, NULL, ecran, &pos);
	      }
	  }
      }
    SDL_Flip(ecran);
    //SDL_FreeSurface(rectangle_b);
    //SDL_FreeSurface(rectangle_r);
    return (0);
  }

  void close_window()
  {
    SDL_Quit();
  }

  /*  void init_window_pac()
  {
    SDL_Init(SDL_INIT_VIDEO);
  }*/
    
  void init_window()
  {
    SDL_Init(SDL_INIT_VIDEO);
  }

  int check_key(int ch, int *ch2)
  {
    if (ch == SDLK_UP || ch == SDLK_z)
      {
        *ch2 = ch;
        return (0);
      }
    else if (ch == SDLK_LEFT || ch == SDLK_q)
      {
        *ch2 = ch;
        return (3);
      }
    else if (ch == SDLK_RIGHT || ch == SDLK_d)
      {
        *ch2 = ch;
        return (2);
      }
    else if (ch == SDLK_DOWN || ch == SDLK_s)
      {
        *ch2 = ch;
        return (1);
      }
    else if (ch == 233)
      {
	close_window();
	return (21);
      }
    else if (ch == 34)
      {
	close_window();
	return (-21);
      }
    else if (ch == 45)
      {
	close_window();
	return (100);
      }
    else if (ch == 39 || ch == 40) 
      {
	close_window();
	return (10);
      }
    else if (ch == 95)
      {
	close_window();
	return (-10);
      }
    return (42);
  }

  int get_key()
  {
    SDL_Event event;

    if (SDL_PollEvent(&event))
      return (event.key.keysym.sym);
    return (-1);
  }
}
