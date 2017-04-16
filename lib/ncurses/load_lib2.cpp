/*
** ncurses_pacman.cpp for arcade
**
** Made by	Vincent Pain
** Login	<vincent.pain@epitech.eu>
**
** Started on	Tue Apr 04 14:06:22 2017 Vincent Pain
** Last update	Tue Apr 04 15:39:53 2017 Vincent Pain
*/

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <ncurses.h>

#include "snake.hpp"

extern "C"
{
  /*  void init_window_pac()
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
    }*/

  void        display_map_pac(char map[21][20])
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
	    else if  (map[i][o] == 'a')
	      {
	        attron(A_REVERSE);
	        attron(COLOR_PAIR(2));
		mvprintw(i + center_lines, o + center_cols, " ");
	        attroff(COLOR_PAIR(2));
	        attroff(A_REVERSE);
	      }
	    else if  (map[i][o] == 'b')
	      {
	        attron(A_REVERSE);
	        attron(COLOR_PAIR(3));
		mvprintw(i + center_lines, o + center_cols, " ");
	        attroff(COLOR_PAIR(3));
	        attroff(A_REVERSE);
	      }
	    else if  (map[i][o] == 'c')
	      {
	        attron(A_REVERSE);
	        attron(COLOR_PAIR(4));
		mvprintw(i + center_lines, o + center_cols, " ");
	        attroff(COLOR_PAIR(4));
	        attroff(A_REVERSE);
	      }
	    else if  (map[i][o] == 'd')
	      {
	        attron(A_REVERSE);
	        attron(COLOR_PAIR(5));
		mvprintw(i + center_lines, o + center_cols, " ");
	        attroff(COLOR_PAIR(5));
	        attroff(A_REVERSE);
	      }
	    else if  (map[i][o] != '*' && map[i][o] != '0')
	      {
	        attron(A_REVERSE);
	        attron(COLOR_PAIR(6));
		mvprintw(i + center_lines, o + center_cols, " ");
	        attroff(COLOR_PAIR(6));
	        attroff(A_REVERSE);
	      }
	    else
	      mvprintw(i + center_lines, o + center_cols, " ");
	  }
      }
  }
}
