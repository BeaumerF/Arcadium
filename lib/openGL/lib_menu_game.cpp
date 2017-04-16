//
// lib_menu.cpp for lib_menu in /home/demangeq/Documents/annee_2/C++/cpp_arcade/lib/sdl
// 
// Made by demangq
// Login   <quentin.demange@epitech.eu>
// 
// Started on  Thu Apr  6 15:35:46 2017 demangq
// Last update Sun Apr  9 17:33:39 2017 François Beaumer
//

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/freeglut_ext.h>

#define LARGEUR_ECRAN 735
#define HAUTEUR_ECRAN 665

extern "C" 
{
  void load_lib() __attribute__ ((constructor));

  void close_lib() __attribute__ ((destructor));

  void load_lib()
  {
    printf("Loading menu game openGL\n");
  }

  void close_lib()
  {
    printf("Unloading menu game openGL\n");
  }

  void drawBeveledSquare(double largeur,double hauteur, int R, int G, int B)
  {
    glColor3ub(R, G, B);
    glBegin(GL_QUADS);
    glVertex2d(0, hauteur - 10);
    glVertex2d(10, hauteur);
    glVertex2d(largeur - 10, hauteur);
    glVertex2d(largeur, hauteur - 10);
    glVertex2d(largeur, 10);
    glVertex2d(largeur - 10, 0);
    glVertex2d(10,0);
    glVertex2d(0,10);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(0, hauteur - 10);
    glVertex2d(largeur, hauteur - 10);
    glVertex2d(largeur, 10);
    glVertex2d(0,10);
    glEnd();
  }

  void drawSelect(double largeur,double hauteur, int R, int G, int B)
  {
    glColor3ub(R, G, B);
    glBegin(GL_QUADS);
    glVertex2d(-2, hauteur - 8);
    glVertex2d(8, hauteur + 2);
    glVertex2d(largeur - 8, hauteur + 2);
    glVertex2d(largeur + 2, hauteur - 8);
    glVertex2d(largeur + 2, 8);
    glVertex2d(largeur - 8, -2);
    glVertex2d(8,-2);
    glVertex2d(-2,8);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(0, hauteur - 10);
    glVertex2d(largeur, hauteur - 10);
    glVertex2d(largeur, 10);
    glVertex2d(0,10);
    glEnd();
  }

  void drawStrokeText(const char *string,int x,int y,int z)
  {
	  const char *c;
    glColor3ub(255, 255, 255);    
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	  glScalef(0.29f, 0.18f,z);
  
	  for (c = string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
	  }
	  glPopMatrix();
  }

  void        display_menu_game(int choice)
  {
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glTranslated(183, 261, 0);
    if (choice == 0)
      drawSelect(367, 60, 255, 255, 255);
    drawBeveledSquare(367, 60, 123, 15, 213);
    drawStrokeText("SNAKE", 110, 15 ,0);
    glTranslated(0, 80, 0);
    if (choice == 1)
      drawSelect(367, 60, 255, 255, 255);
    drawBeveledSquare(367, 60, 213, 173, 53);
    drawStrokeText("PAC-MAN", 80, 15, 0);
    glFlush();
    SDL_GL_SwapBuffers();
  }

  void close_window()
  {
    SDL_Quit();
  }

  void init_window()
  {
    char *myargv [1];
    int myargc=1;

    myargv [0]=strdup ("Menu");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Menu", NULL);
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,LARGEUR_ECRAN,0,HAUTEUR_ECRAN);
    SDL_EnableKeyRepeat(300, 30);
    glutExit();
    glutInit(&myargc, myargv);
  }

  int check_key(int ch)
    {
      static int select = 0;

      if (ch == SDLK_UP || ch == SDLK_z)
        {
          if (select == 1)
              select = 0;
          else
              select++;
        }
      else if (ch == SDLK_DOWN || ch == SDLK_s)
        {
          if (select == 0)
              select = 1;
          else
              select--;
        }
      else if (ch == 27)
        {
        close_window();
        return (27);
        }
      return (select);
    }

    int get_key()
    {
      SDL_Event event;

      while (SDL_PollEvent(&event));
      return (event.key.keysym.sym);
    }

}
