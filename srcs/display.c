/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efiorent <efiorent@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:55:03 by efiorent          #+#    #+#             */
/*   Updated: 2026/04/25 14:29:58 by efiorent         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "display.h"
#include "font.h"
#include "libft.h"
#include <ncurses.h>
#include <stddef.h>

#define INIT_COLORS(color) init_pair(color, COLOR_WHITE, color);
#define INVERSE_COLORS(print) \
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

static void	display_cell_border(int x, int y)
{
	const size_t CELL_SIZE = (COLS > 100) ? CELL_SIZE_L: CELL_SIZE_S;
	const size_t CELL_WIDTH = CELL_SIZE * 2;
	const size_t CELL_WALL_WIDTH = CELL_WALL_SIZE * 2;

	attron(COLOR_PAIR(BOARD_WALL_COLOR));
	// top border
	for (size_t i = 0; i < CELL_WIDTH; i++)
		for (size_t j = 0; j < CELL_WALL_SIZE; j++)
			mvaddch(y + j, x + i, ' ');
	// bottom border
	for (size_t i = 0; i < CELL_WIDTH; i++)
		for (size_t j = 0; j < CELL_WALL_SIZE; j++)
			mvaddch(y + CELL_SIZE - j - 1, x + i, ' ');
	// left border
	for (size_t i = 0; i < CELL_SIZE; i++)
		for (size_t j = 0; j < CELL_WALL_WIDTH; j++)
			mvaddch(y + i, x + j, ' ');
	// right border
	for (size_t i = 0; i < CELL_SIZE; i++)
		for (size_t j = 0; j < CELL_WALL_WIDTH; j++)
			mvaddch(y + i, x + CELL_WIDTH - j - 1, ' ');
	attroff(COLOR_PAIR(BOARD_WALL_COLOR));
}

static void	display_cell_number(int nb, int x, int y, int size)
{
	if (nb <= 0)
		return ;
	const size_t CELL_SIZE = (COLS > 100) ? CELL_SIZE_L: CELL_SIZE_S;
	int len = 0;
	for (int tmp_nb = nb; tmp_nb != 0; tmp_nb /= 10)
		len++;
	int x_pos = x + CELL_SIZE - 1;
	int y_pos = y + CELL_SIZE / 2;
	if (COLS < 100)
		mvprintw(y_pos, x + CELL_SIZE - (len + 1) / 2, "%d", nb);
	else
		COLOR(COLOR_YELLOW, print_number(x_pos, y_pos, nb, size));
}

void	display_board(t_board *board)
{
	const size_t	CELL_SIZE = (COLS > 100) ? CELL_SIZE_L: CELL_SIZE_S;
	const size_t	CELL_WIDTH = CELL_SIZE * 2 - CELL_WALL_SIZE * 2;
	const size_t	CELL_HEIGHT = CELL_SIZE - CELL_WALL_SIZE;
	int	x = COLS / 2 - (CELL_WIDTH * board->size) / 2;
	int	y = LINES / 2 - (CELL_HEIGHT * board->size) / 2;
	for (size_t i = 0; i < board->size; i++)
		for (size_t j = 0; j < board->size; j++)
			display_cell_border(x + i * CELL_WIDTH, y + j * CELL_HEIGHT);
	for (size_t i = 0; i < board->size; i++)
		for (size_t j = 0; j < board->size; j++)
		{
			int size = (board->grid[i][j] >= 1000)? 1: 2;
			display_cell_number(board->grid[i][j], x + j * CELL_WIDTH, y + i * CELL_HEIGHT, size);
		}
}

int	display_main_menu(t_font *font)
{
	char *logo_str = "2048";
	int xlogo = COLS / 2 - ft_strlen(logo_str) * FONT_WIDTH;
	int ylogo = LINES / 4;

	char *s1 = "4x4 board";
	int x1 = COLS / 2 - ft_strlen(s1) / 2;
	int y1 = LINES - LINES / 3;

	char *s2 = "5x5 board";
	int x2 = COLS / 2 - ft_strlen(s2) / 2;
	int y2 = y1 + 2;

	int selected_choice = 4;
	while (true)
	{
		erase();
		COLOR(COLOR_YELLOW, print(font, xlogo, ylogo, logo_str));
		if (selected_choice == 4)
			INVERSE_COLORS(mvprintw(y1, x1, "%s", s1));
		else
			mvprintw(y1, x1, "%s", s1);
		if (selected_choice == 5)
			INVERSE_COLORS(mvprintw(y2, x2, "%s", s2));
		else
			mvprintw(y2, x2, "%s", s2);
		refresh();
		int k = getch();
		if (k == 'q' || k == KEY_ESCAPE)
			return (ERR);
		if (k == KEY_UP || k == KEY_DOWN)
			selected_choice = (selected_choice + 1) % 2 + 4;
		if (k == '\n' || k == ' ')
			return (selected_choice);
	}
	return (ERR);
}
