/*
** pacman.cpp for arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Tue Apr 04 14:37:28 2017 Vincent Pain
** Last update	Tue Apr 04 15:39:52 2017 Vincent Pain
*/

#include "pacman.hpp"

extern "C"
{
  int           put_feed(char tab[21][20]);
  int		game_over(char tab[LENGHT][WIDTH]);
  void		move_phantom(char tab[LENGHT][WIDTH], t_phantom *ph);
  int		teleport(char tab[LENGHT][WIDTH]);
  void		init_phantom(char tab[LENGHT][WIDTH], int *mod);
  int		pac_move(char tab[LENGHT][WIDTH], int y, int x);
}

  int           put_feed(char tab[21][20])
  {
    int food = 0;
    
    for (int i = 0; i < 21 ; i++)
      {
	for (int o = 0; o < 19; o++)
	  {
	    if (tab[i][o] == '$')
	      food = 1;
	  }
      }
    if (food == 0)
      {
	printf("GG WP\n");
	return (42);
      }
    return (0);
  }

  int		game_over(char tab[LENGHT][WIDTH])
  {
    int           cursy = -1;
    int           cursx = -1;
    int           stop = 0;

    while (stop != 42 && ++cursy < LENGHT - 1)
      {
	cursx = -1;
	while (stop != 42 && ++cursx < WIDTH - 1)
	  if (tab[cursy][cursx] == '1')
	    stop = 42;
      }
    return (stop);
  }

  void		move_phantom(char tab[LENGHT][WIDTH], t_phantom *ph)
  {
    int		cursy = -1;
    int		cursx = -1;
    int		stop = -1;

    while (stop != 42 && ++cursy < LENGHT - 1)
      {
	cursx = -1;
	while (stop != 42 && ++cursx < WIDTH - 1)
	  if (tab[cursy][cursx] == ph->c)
	    stop = 42;
      }
    if (stop == 42)
      {
	int	dir = (rand() % 4);
	int	verif = 0;
	if (ph->last_dir == 0  && tab[cursy][cursx + 1] != '*')
	  {
	    tab[cursy][cursx] = ph->last;
	    ph->last = tab[cursy][cursx + 1];
	    tab[cursy][cursx + 1] = ph->c;
	  }
	else if (ph->last_dir == 1 && tab[cursy][cursx - 1] != '*')
	  {
	    tab[cursy][cursx] = ph->last;
	    ph->last = tab[cursy][cursx - 1];
	    tab[cursy][cursx - 1] = ph->c;
	  }
	else if (ph->last_dir == 2 && tab[cursy + 1][cursx] != '*')
	  {
	    tab[cursy][cursx] = ph->last;
	    ph->last = tab[cursy + 1][cursx];
	    tab[cursy + 1][cursx] = ph->c;
	  }
	else if (ph->last_dir == 3 && tab[cursy - 1][cursx] != '*')
	  {
	    tab[cursy][cursx] = ph->last;
	    ph->last = tab[cursy - 1][cursx];
	    tab[cursy - 1][cursx] = ph->c;
	  }
	else
	  while (verif == 0)
	    {
	      tab[cursy][cursx] = ph->last;
	      if (dir == 0 && tab[cursy][cursx + 1] != '*')
		{
		  ph->last_dir = 0;
		  verif = 1;
		  ph->last = tab[cursy][cursx + 1];
		  tab[cursy][cursx + 1] = ph->c;
		}
	      else if (dir == 1 && tab[cursy][cursx - 1] != '*')
		{
		  ph->last_dir = 1;
		  verif = 2;
		  ph->last = tab[cursy][cursx - 1];
		  tab[cursy][cursx - 1] = ph->c;
		}
	      else if (dir == 2 && tab[cursy + 1][cursx] != '*')
		{
		  ph->last_dir = 2;
		  verif = 3;
		  ph->last = tab[cursy + 1][cursx];
		  tab[cursy + 1][cursx] = ph->c;
		}
	      else if (dir == 3 && tab[cursy - 1][cursx] != '*')
		{
		  ph->last_dir = 3;
		  verif = 4;
		  ph->last = tab[cursy - 1][cursx];
		  tab[cursy - 1][cursx] = ph->c;
		}
	      dir = (rand() % 4);
	    }
      }
  }

  int		teleport(char tab[LENGHT][WIDTH])
  {
    if (tab[LENGHT/2 - 1][0] != '0')
      {
	tab[LENGHT/2 - 1][WIDTH - 2] = tab[LENGHT/2 - 1][0];
	tab[LENGHT/2 - 1][0] = '0';
      }
    else if (tab[LENGHT/2 - 1][WIDTH - 2] != '0')
      {
	tab[LENGHT/2 - 1][1] = tab[LENGHT/2 - 1][WIDTH - 2];
	tab[LENGHT/2 - 1][WIDTH - 2] = '0';
      }
    return (0);
  }

  void		init_phantom(char tab[LENGHT][WIDTH], int *mod)
  {
    if ((tab[LENGHT/2 - 3][WIDTH/2 - 1] == '0' ||
	 tab[LENGHT/2 - 3][WIDTH/2 - 1] == '$'))
      {
	if (mod[0] <= 40)
	  ++mod[0];
	if (mod[0] == 1)
	  tab[LENGHT/2 - 3][WIDTH/2 - 1] = 'a';
	else if (mod[0] == 10)
	  tab[LENGHT/2 - 3][WIDTH/2 - 1] = 'b';
	else if (mod[0] == 20)
	  tab[LENGHT/2 - 3][WIDTH/2 - 1] = 'd';
	else if (mod[0] == 30)
	  tab[LENGHT/2 - 3][WIDTH/2 - 1] = 'c';
      }
  }

  int		pac_move(char tab[LENGHT][WIDTH], int y, int x)
  {
    int		cursy = -1;
    int		cursx = -1;
    int		stop = 0;

    while (stop != 42 && ++cursy < LENGHT - 1)
      {
	cursx = -1;
	while (stop != 42 && ++cursx < WIDTH - 1)
	  if (tab[cursy][cursx] == '1')
	    stop = 42;
      }
    tab[cursy][cursx] = '0';
    if (tab[cursy + y][cursx + x] == '0')
      tab[cursy + y][cursx + x] = '1';
    else if (tab[cursy + y][cursx + x] == '$')
      tab[cursy + y][cursx + x] = '1';
    else
      tab[cursy][cursx] = '1';
    return (0);
  }