/*
** ncurses_pacman.cpp for arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Tue Apr 04 14:06:22 2017 Vincent Pain
** Last update	Tue Apr 04 15:39:53 2017 Vincent Pain
*/

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include "pacman.hpp"

#define SIZE_CUBE       40
#define LARGEUR_ECRAN (WIDTH * SIZE_CUBE) - SIZE_CUBE
#define HAUTEUR_ECRAN (LENGHT * SIZE_CUBE)

extern "C"
{
  void drawSquare(double size, int R, int G, int B)
  {
    glColor3ub(R, G, B);
    glBegin(GL_QUADS);
    glVertex2d(0, size);
    glVertex2d(size, size);
    glVertex2d(size, 0);
    glVertex2d(0,0);
    glEnd();
  }

  void      drawCandy(double size, int R, int G, int B)
  {
    glColor3ub(R, G, B);
    glBegin(GL_QUADS);
    glVertex2d(15, size - 15);
    glVertex2d(size - 15, size - 15);
    glVertex2d(size - 15, 15);
    glVertex2d(15,15);
    glEnd();
  }

  int        display_map_pac(char tab[LENGHT][WIDTH])
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
    		drawSquare(SIZE_CUBE, 48, 4, 213);
	    else if (tab[y][x] == '$')
	    	drawCandy(SIZE_CUBE, 255, 210, 170);
	    else if (tab[y][x] == 'a')
	    	drawSquare(SIZE_CUBE, 247, 87, 97);
	    else if (tab[y][x] == 'b')
	    	drawSquare(SIZE_CUBE, 23, 180, 233);
	    else if (tab[y][x] == 'c')
	    	drawSquare(SIZE_CUBE, 241, 153, 178);
	    else if (tab[y][x] == 'd')
	    	drawSquare(SIZE_CUBE, 237, 27, 36);
	    else if (tab[y][x] != '*' && tab[y][x] != '0')
	    	drawSquare(SIZE_CUBE, 255, 255, 0);	    
        else
    		drawSquare(SIZE_CUBE, 0, 0, 0);
	    glTranslated(SIZE_CUBE, 0, 0);
	  }
	glTranslated(-((WIDTH * SIZE_CUBE) - SIZE_CUBE), -SIZE_CUBE, 0);
      }
    glFlush();
    SDL_GL_SwapBuffers();
  }
}
