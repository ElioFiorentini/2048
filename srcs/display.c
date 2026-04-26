/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:55:03 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/26 18:19:44 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "display.h"
#include "font.h"
#include "utils.h"
#include <ncurses.h>
#include <stddef.h>

#define INIT_COLORS(color) init_pair(color, COLOR_WHITE, color);
#define INVERT_COLORS(print) \
	do {\
		attron(A_REVERSE);\
		(print);\
		attroff(A_REVERSE);\
	} while (0)
#define COLOR(color, print) \
	do {\
		attron(COLOR_PAIR(color));\
		(print);\
		attroff(COLOR_PAIR(color));\
	} while (0)

void	init_all_color_pair()
{
	INIT_COLORS(COLOR_BLACK);
	INIT_COLORS(COLOR_RED);
	INIT_COLORS(COLOR_GREEN);
	INIT_COLORS(COLOR_YELLOW);
	INIT_COLORS(COLOR_BLUE);
	INIT_COLORS(COLOR_MAGENTA);
	INIT_COLORS(COLOR_CYAN);
	INIT_COLORS(COLOR_WHITE);
}

static void	display_cell_border(int x, int y, const size_t CELL_WIDTH, const size_t CELL_HEIGHT)
{
	attron(COLOR_PAIR(BOARD_WALL_COLOR));
	for (size_t i = 0; i < CELL_WIDTH; i++)
	{
		mvaddch(y, x + i, ' ');
		mvaddch(y + CELL_HEIGHT - 1, x + i, ' ');
	}
	for (size_t i = 0; i < CELL_HEIGHT; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			mvaddch(y + i, x + j, ' ');
			mvaddch(y + i, x + j + CELL_WIDTH - 2, ' ');
		}
	}
	attroff(COLOR_PAIR(BOARD_WALL_COLOR));
}

static void	display_cell_number(int nb, int x, int y, const size_t CELL_WIDTH, const size_t CELL_HEIGHT)
{
	if (nb <= 0)
		return ;
	size_t len = nbrlen(nb);
	size_t text_width = 3 * len + (len - 1);
	size_t text_size = (text_width + 3 * len > CELL_WIDTH - 4)? 1: 2;
	if (text_size == 2)
		text_width += 3 * len;
	int x_pos = x + CELL_WIDTH / 2;
	int y_pos = y + CELL_HEIGHT / 2;
	if (text_width > CELL_WIDTH - 4 || CELL_HEIGHT - 2 < 5)
		mvprintw(y_pos, x_pos - len / 2, "%d", nb);
	else
		COLOR(COLOR_YELLOW, print_number(x_pos, y_pos, nb, text_size));
}

void	display_board(t_board *board)
{
	const size_t	H_PADDING = COLS * 0.3;
	const size_t	V_PADDING = LINES * 0.1;
	const size_t	CELL_WIDTH = max((COLS - H_PADDING) / board->size + 1, MIN_CELL_WIDTH);
	const size_t	CELL_HEIGHT = max((LINES - V_PADDING) / board->size + 1, MIN_CELL_HEIGHT);
	int	y = V_PADDING / 2;
	for (size_t i = 0; i < board->size; i++)
	{
		int	x = H_PADDING / 2;
		for (size_t j = 0; j < board->size; j++)
		{
			display_cell_border(x, y, CELL_WIDTH, CELL_HEIGHT);
			display_cell_number(board->grid[i][j], x, y, CELL_WIDTH, CELL_HEIGHT);
			x += CELL_WIDTH - 2;
		}
		y += CELL_HEIGHT - 1;
	}
}

static void	display_menu_choice(bool invert, int x, int y, char *s)
{
	if (invert)
		INVERT_COLORS(mvprintw(y, x, "%s", s));
	else
		mvprintw(y, x, "%s", s);
}

static void	display_logo(t_font *font, const int LOGO_WIDTH, char *logo_str)
{
	int xlogo = COLS / 2 - LOGO_WIDTH;
	int ylogo = LINES / 4;
	if (LOGO_WIDTH * 2 < COLS)
		COLOR(COLOR_YELLOW, print(font, xlogo, ylogo, logo_str, 2));
	else if (LOGO_WIDTH < COLS)
	{
		xlogo = COLS / 2 - LOGO_WIDTH / 2;
		COLOR(COLOR_YELLOW, print(font, xlogo, ylogo, logo_str, 1));
	}
	else
	{
		xlogo = COLS / 2 - ft_strlen(logo_str) / 2;
		ylogo = LINES / 2;
		mvprintw(ylogo, xlogo, "%s", logo_str);
	}
}

int	display_main_menu(t_font *font)
{
	char		*logo_str = "2048";
	char		*s1 = " 4x4 board ";
	char		*s2 = " 5x5 board ";
	char		*s3 = " Quit ";
	const int	LOGO_WIDTH = ft_strlen(logo_str) * FONT_WIDTH;

	int selected_choice = 4;
	while (true)
	{
		int x1 = COLS / 2 - ft_strlen(s1) / 2;
		int y1 = LINES - LINES / 3;
		int x2 = COLS / 2 - ft_strlen(s2) / 2;
		int y2 = y1 + 2;
		int x3 = COLS / 2 - ft_strlen(s3) / 2;
		int y3 = y2 + 2;
		erase();
		display_logo(font, LOGO_WIDTH, logo_str);
		display_menu_choice(selected_choice == 4, x1, y1, s1);
		display_menu_choice(selected_choice == 5, x2, y2, s2);
		display_menu_choice(selected_choice == 6, x3, y3, s3);
		refresh();

		int k = getch();
		if (k == 'q' || k == KEY_ESCAPE)
			return (ERR);
		if (k == KEY_UP)
			selected_choice = (selected_choice + 1) % 3 + 4;
		if (k == KEY_DOWN)
			selected_choice = (selected_choice + 3) % 3 + 4;
		if (k == '\n' || k == ' ')
			return (selected_choice);
	}
	return (ERR);
}

int	display_end_menu(t_font *font)
{
	char		*logo_str = "Victory";
	char		*s1 = " Continue to play ";
	char		*s2 = " Quit ";
	const int	LOGO_WIDTH = ft_strlen(logo_str) * FONT_WIDTH;

	int selected_choice = 0;
	while (true)
	{
		int x1 = COLS / 2 - ft_strlen(s1) / 2;
		int y1 = LINES - LINES / 3;
		int x2 = COLS / 2 - ft_strlen(s2) / 2;
		int y2 = y1 + 2;
		erase();
		display_logo(font, LOGO_WIDTH, logo_str);
		display_menu_choice(selected_choice == 0, x1, y1, s1);
		display_menu_choice(selected_choice == 1, x2, y2, s2);
		refresh();

		int k = getch();
		if (k == 'q' || k == KEY_ESCAPE)
			return (ERR);
		if (k == KEY_UP || k == KEY_DOWN)
			selected_choice = (selected_choice + 1) % 2;
		if (k == '\n' || k == ' ')
			return (selected_choice);
	}
	return (ERR);
}

int	display_game_over(t_font *font)
{
	char		*logo_str = "Game Over";
	char		*s1 = " Play again ";
	char		*s2 = " Quit ";
	const int	LOGO_WIDTH = ft_strlen(logo_str) * FONT_WIDTH;

	int selected_choice = OK;
	while (true)
	{
		int x1 = COLS / 2 - ft_strlen(s1) / 2;
		int y1 = LINES - LINES / 3;
		int x2 = COLS / 2 - ft_strlen(s2) / 2;
		int y2 = y1 + 2;
		erase();
		display_logo(font, LOGO_WIDTH, logo_str);
		display_menu_choice(selected_choice == OK, x1, y1, s1);
		display_menu_choice(selected_choice == ERR, x2, y2, s2);
		refresh();

		int k = getch();
		if (k == 'q' || k == KEY_ESCAPE)
			return (ERR);
		if (k == KEY_UP || k == KEY_DOWN)
			selected_choice = (selected_choice + 2) % 2 - 1;
		if (k == '\n' || k == ' ')
			return (selected_choice);
	}
	return (ERR);
}
