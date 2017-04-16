/*
** snake.cpp for cpp_arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Fri Mar 17 16:30:00 2017 Vincent Pain
** Last update	Tue Mar 28 16:34:35 2017 Vincent Pain
*/

#include "snake.hpp"

extern "C"
{
  void		snake_tail(char tab[LENGHT][WIDTH], int *tail);
  int            put_feed(char tab[LENGHT][WIDTH]);
  void		add_tail(char tab[LENGHT][WIDTH], int y, int x, int *tail);
  int		snake_move(char tab[LENGHT][WIDTH], int y, int x, int *tail);
}

void		snake_tail(char tab[LENGHT][WIDTH], int *tail)
  {
    int           cursy = -1;
    int           cursx = -1;
    int           stop = 0;

    while (stop != 42 && ++cursy < LENGHT - 1)
      {
        cursx = -1;
        while (stop != 42 && ++cursx < WIDTH - 1)
  	if (tab[cursy][cursx] == *tail + '0')
  	  tab[cursy][cursx] = '0';
      }
    cursy = -1;
    cursx = -1;
    while (stop != 42 && ++cursy < LENGHT - 1)
      {
        cursx = -1;
        while (stop != 42 && ++cursx < WIDTH - 1)
  	if (tab[cursy][cursx] < *tail + '0' && tab[cursy][cursx] >= '1')
  	  tab[cursy][cursx] += 1;
      }

  }

  int            put_feed(char tab[LENGHT][WIDTH])
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

      if (food == 0) {
          int x = (rand() % 17) + 1;
          int y = (rand() % 19) + 1;
          while (tab[y][x] != '0')
          {
              x = (rand() % 17) + 1;
              y = (rand() % 19) + 1;
          }
          tab[y][x] = '$';
      }
    return (0);
  }

  void		add_tail(char tab[LENGHT][WIDTH], int y, int x, int *tail)
  {
    int           cursy = -1;
    int           cursx = -1;
    int           stop = 0;
    int		dirx = 0;
    int		diry = 0;

    while (stop != 42 && ++cursy < LENGHT - 1)
      {
        cursx = -1;
        while (stop != 42 && ++cursx < WIDTH - 1)
  	if (tab[cursy][cursx] == *(tail) + '0')
  	  stop = 42;
      }
    if (y == -1)
      diry = 1;
    else if (y == 1)
      diry = -1;
    else if (x == -1)
      dirx = 1;
    else if (x == 1)
      dirx = -1;
    tab[cursy + diry][cursx + dirx] = *(tail) + '0' + 1;
    //std::cout << tab[cursy + diry][cursx + dirx] << std::endl;
    ++tail[0];
  }
  
  int		snake_move(char tab[LENGHT][WIDTH], int y, int x, int *tail)
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
    if (tab[cursy + y][cursx + x] == '0')
      {
        snake_tail(tab, tail);
        tab[cursy + y][cursx + x] = '1';
      }
    else if (tab[cursy + y][cursx + x] == '$')
      {
        snake_tail(tab, tail);
        add_tail(tab, y, x, tail);
        tab[cursy + y][cursx + x] = '1';
      }
    else
      return (42);
    return (0);
  }
