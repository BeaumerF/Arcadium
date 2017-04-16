/*
** load_lib.cpp for cpp_arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Tue Mar 14 16:45:00 2017 Vincent Pain
** Last update	Tue Apr 04 13:56:40 2017 Vincent Pain
*/

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <ncurses.h>

#include "snake.hpp"

extern "C"

{
  void load_lib() __attribute__ ((constructor));

  void close_lib() __attribute__ ((destructor));

  void load_lib()
  {
    printf("Loading ncurses\n");
  }

  void close_lib()
  {
    printf("Unloading ncurses\n");
  }

  int        display_map(char map[LENGHT][WIDTH])
  {
    int         center_lines = (LINES / 2) - 11;
    int         center_cols = (COLS / 2) - 11;
    for (int i = 0; i < 21 ; i++)
      {
        for (int o = 0; o < 19; o++)
  	    {
          if (map[i][o] == '*')
          {
  	        attron(A_REVERSE);
  	        mvprintw(i + center_lines , o + center_cols, " ");
  	        attroff(A_REVERSE);
          }
          else if (map[i][o] == '$')
          {
              attron(COLOR_PAIR(1));
              mvprintw(i + center_lines, o + center_cols, "@");
              attroff(COLOR_PAIR(1));
          }
          else if  (map[i][o] != '*' && map[i][o] != '0')
          {
  	        attron(A_REVERSE);
  	        attron(COLOR_PAIR(2));
              mvprintw(i + center_lines, o + center_cols, " ");
  	        attroff(COLOR_PAIR(2));
  	        attroff(A_REVERSE);
          }
          else
            mvprintw(i + center_lines, o + center_cols, " ");
  	    }
      }
    return (0);
  }

  void close_window()
  {
    endwin();
  }

  void init_window()
  {
    if (newterm(NULL, stderr, stdin) == NULL)
      return ;
    start_color();
    init_color(COLOR_CYAN, 1000, 500, 800);
    init_color(COLOR_WHITE, 1000, 400, 0);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
  }

  int check_key(int ch, int *ch2)
  {
    if (ch == KEY_UP || ch == 122)
      {
        *ch2 = ch;
        return (0);
      }
    else if (ch == KEY_LEFT || ch == 113)
      {
        *ch2 = ch;
        return (3);
      }
    else if (ch == KEY_RIGHT || ch == 100)
      {
        *ch2 = ch;
        return (2);
      }
    else if (ch == KEY_DOWN || ch == 115)
      {
        *ch2 = ch;
        return (1);
      }
    else if (ch == 195)
      {
	close_window();
	return (21);
      }
    else if (ch == 45)
      {
	close_window();
	return (100);
      }
    else if (ch == 34)
      {
	close_window();
	return (-21);
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
    nodelay(stdscr, TRUE);
    return (getch());
  }
}
