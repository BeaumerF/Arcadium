//
// load_lib.cpp for load_libb in /home/demangeq/Documents/annee_2/C++/cpp_arcade/lib/openGL
// 
// Made by demangq
// Login   <quentin.demange@epitech.eu>
// 
// Started on  Mon Apr  3 14:26:12 2017 demangq
// Last update Sun Apr  9 19:33:23 2017 François Beaumer
//


#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include "snake.hpp"

#define SIZE_CUBE	40
#define LARGEUR_ECRAN (WIDTH * SIZE_CUBE) - SIZE_CUBE
#define HAUTEUR_ECRAN (LENGHT * SIZE_CUBE)

extern "C"

{
  void load_lib() __attribute__ ((constructor));

  void close_lib() __attribute__ ((destructor));
  
  void load_lib()
  {
    printf("Loading openGL\n");
  }
  
  void close_lib()
  {
    printf("Unloading openGL\n");
  }
  
  void dessineRectangle(double largeur,double hauteur)
  {
    glBegin(GL_QUADS);
    glVertex2d(0, hauteur);
    glVertex2d(largeur, hauteur);
    glVertex2d(largeur, 0);
    glVertex2d(0,0);
    glEnd();
  }
  
  void dessinerRepere(unsigned int echelle)
  {
    glPushMatrix();
    glScalef(echelle,echelle,echelle);
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
    glVertex2i(0,0);
    glVertex2i(1,0);
    glColor3ub(0,255,0);
    glVertex2i(0,0);
    glVertex2i(0,1);
    glEnd();
    glPopMatrix();
  }
  
  int        display_map(char tab[LENGHT][WIDTH])
  {
    int     x;
    int     y;
    int	    tmpx, tmpy = 0;
    
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glTranslated(0, HAUTEUR_ECRAN - SIZE_CUBE, 0);
    for (int y = 0; y < LENGHT; y++)
      {
	for (int x = 0; x < WIDTH - 1; x++)
	  {
	    if (tab[y][x] == '*')
	      {
		glColor3ub(255,255,255);
		dessineRectangle(SIZE_CUBE, SIZE_CUBE);
	      }
	    else if (tab[y][x] == '$')
	      {
		glColor3ub(255,0,0);
		dessineRectangle(SIZE_CUBE, SIZE_CUBE);
	      }
	    else if (tab[y][x] != '0')
	      {
		glColor3ub(0,255,0);
		dessineRectangle(SIZE_CUBE, SIZE_CUBE);
	      }
	    else
	      {
		glColor3ub(0,0,0);
		dessineRectangle(SIZE_CUBE, SIZE_CUBE);
	      }
	    glTranslated(SIZE_CUBE, 0, 0);
	  }
	glTranslated(-((WIDTH * SIZE_CUBE) - SIZE_CUBE), -SIZE_CUBE, 0);
      }
    glFlush();
    SDL_GL_SwapBuffers();
  }
  
  
  void close_window()
  {
    SDL_Quit();
  }
  
  void init_window()
  {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Snake", NULL);
    SDL_SetVideoMode(LENGHT * SIZE_CUBE, WIDTH * SIZE_CUBE, 32, SDL_OPENGL);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,LARGEUR_ECRAN,0,HAUTEUR_ECRAN);
    // SDL_EnableKeyRepeat(10,10);
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
