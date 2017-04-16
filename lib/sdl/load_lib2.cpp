//
// load_lib2.cpp for arcade in /home/MiniThug/rendu/cpp_arcade/lib/sdl
// 
// Made by Vincent Pain
// Login   <MiniThug@epitech.net>
// 
// Started on  Wed Apr  5 12:47:05 2017 Vincent Pain
// Last update Wed Apr  5 13:32:14 2017 Vincent Pain
//

#include <SDL/SDL.h>
#include "pacman.hpp"

extern "C"
{
  void  display_map_pac(char    tab[LENGHT][WIDTH])
  {
    SDL_Rect pos;
    SDL_Surface *ecran = NULL;
    t_color color;

    ecran = SDL_SetVideoMode(665, 735, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Pacman", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 97, 97, 97));
    color.mur = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    color.chemin = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    color.pacman = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    color.nouriture = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    color.fantome_rose = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    color.fantome_bleu = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    color.fantome_rouge = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    color.fantome_orange = SDL_CreateRGBSurface(SDL_HWSURFACE, 35, 35, 32, 0, 0, 0, 0);
    SDL_FillRect(color.mur, NULL, SDL_MapRGB(ecran->format, 0, 0, 102));
    SDL_FillRect(color.chemin, NULL, SDL_MapRGB(ecran->format, 97, 97, 97));
    SDL_FillRect(color.pacman, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
    SDL_FillRect(color.nouriture, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
    SDL_FillRect(color.fantome_bleu, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
    SDL_FillRect(color.fantome_rouge, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
    SDL_FillRect(color.fantome_rose, NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
    SDL_FillRect(color.fantome_orange, NULL, SDL_MapRGB(ecran->format, 255, 128, 0));
  
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
	      SDL_BlitSurface(color.mur, NULL, ecran, &pos);
	    else if (tab[y][x] == '$')
	      {
		SDL_BlitSurface(color.chemin, NULL, ecran, &pos);
		pos.x += 10;
		pos.y += 10;
		SDL_BlitSurface(color.nouriture, NULL, ecran, &pos);
	      }
	    else if (tab[y][x] == 'a')
	      SDL_BlitSurface(color.fantome_rouge, NULL, ecran, &pos);
	    else if (tab[y][x] == 'b')
	      SDL_BlitSurface(color.fantome_bleu, NULL, ecran, &pos);
	    else if (tab[y][x] == 'c')
	      SDL_BlitSurface(color.fantome_rose, NULL, ecran, &pos);
	    else if (tab[y][x] == 'd')
	      SDL_BlitSurface(color.fantome_orange, NULL, ecran, &pos);
	    else if (tab[y][x] == '1')
	      SDL_BlitSurface(color.pacman, NULL, ecran, &pos);
	    else if (tab[y][x] == '0')
	      SDL_BlitSurface(color.chemin, NULL, ecran, &pos);
	  }
      }
    SDL_Flip(ecran);
  }
}
